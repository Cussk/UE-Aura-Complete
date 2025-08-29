// Copyright Cuss Programming


#include "Player/AuraPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/TargetInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraInputContext);

	//Add mapping context to player
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraInputContext, 0);
	}

	//Show mouse cursor during gameplay
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//Do not lock mouse cursor during play
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRunToDestination();
}

/*
 * Controlled Pawn will move along spline to position within acceptance radius of destination
 */
void AAuraPlayerController::AutoRunToDestination()
{
	if (!bAutoRunning) return;
	
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = SplineComponent->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

/*
 * Bind Actions to input component
 */
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

/*
 * Trace mouse pointer for highlighting actors
 */
void AAuraPlayerController::CursorTrace()
{	
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastTargetActor = CurrentTargetActor;
	CurrentTargetActor = CursorHit.GetActor();

	if (LastTargetActor != CurrentTargetActor)
	{
		if (LastTargetActor)
		{
			LastTargetActor->UnHighlightActor();
		}
		
		if (CurrentTargetActor)
		{
			CurrentTargetActor->HighlightActor();
		}
	}
}

/*
 * Most abilities that use Pressed will also get triggered by Held.
 * Logic for AutoRunToDestination of a Left Click decided here if not touching a target
 */
void AAuraPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	if (IsLMB(InputTag))
	{
		bTargeting = CurrentTargetActor ? true : false;
		bAutoRunning = false;
	}
}

/*
 * Will trigger an on Release ability if not a left click or has a target
 * Will set up the spline points to move destination when left click does not hit a Target
 */
void AAuraPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if (!IsLMB(InputTag) || bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		SetAutoRunSpline();
	}
}

/*
 * Will trigger an on Pressed or Held ability if not a left click or has a target
 * Will move to destination hit point when left click does not hit a Target
 */
void AAuraPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if (!IsLMB(InputTag) || bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		MoveToHitPoint();
	}
}

/*
 * Uses current mouse pointer hit to set a destination point and move to it
 */
void AAuraPlayerController::MoveToHitPoint()
{
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	if (CursorHit.bBlockingHit)
	{
		CachedDestination = CursorHit.ImpactPoint;
	}

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

/*
 * Gets a navigation path along the nav mesh to the CachedDestination and adds it to a spline for the player to auto run along
 */
void AAuraPlayerController::SetAutoRunSpline()
{
	const APawn* ControlledPawn = GetPawn();
	if (FollowTime <= ShortPressThreshold && ControlledPawn)
	{
		if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
		{
			SplineComponent->ClearSplinePoints();
			for (const FVector& PointLocation : NavigationPath->PathPoints)
			{
				SplineComponent->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
				//DrawDebugSphere(GetWorld(), PointLocation, 3.f, 8, FColor::Green, false, 5.f);
			}

			if (NavigationPath->PathPoints.Num() > 0)
			{
				CachedDestination = NavigationPath->PathPoints[NavigationPath->PathPoints.Num() - 1];
			}
				
			bAutoRunning = true;
		}
	}

	FollowTime = 0.f;
	bTargeting = false;
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (!AuraAbilitySystemComponent)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AuraAbilitySystemComponent;
}
