// Copyright Cuss Programming


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	SetupTopDownCamera();
	RotatePlayerToMovement();
}

/*
 * Called when this Pawn is possessed. Only called on the server (or in standalone).
 */
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

/*
 * Fires when Player State is replicated down to client from the server
 */
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability actor info for the client
	InitAbilityActorInfo();
}

/*
 * Creates/initializes Player Camera to be a top-down follow camera
 */
void AAuraCharacter::SetupTopDownCamera()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 750.f;

	//Prevent spring arm rotating with player
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;

	CameraActor = CreateDefaultSubobject<UCameraComponent>("CameraActor");
	CameraActor->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

/*
 * Rotate player avatar to the direction they are moving in
 */
void AAuraCharacter::RotatePlayerToMovement()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//Stops Player from trying to orient based on PlayerController's rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

/*
 * Sets up Player Ability Actor Info, Main HUD, and initial attribute values
 */
void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);

	if (AAuraPlayerController* AuraPlayerController = GetController<AAuraPlayerController>())
	{
		if (AAuraHUD* AuraHUD = AuraPlayerController->GetHUD<AAuraHUD>())
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}

/* GETTERS */

int32 AAuraCharacter::GetCharacterLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetCharacterLevel();
}
