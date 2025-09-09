// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Controller.h"
#include "AuraPlayerController.generated.h"

class UDamageTextComponent;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
class ITargetInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;

/**
 * Class in charge of setting up/defining player inputs
 */
UCLASS()
class AURACOMPLETE_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);

	FHitResult GetCursorHit() {return CursorHit;}
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	static bool IsLMB(const FGameplayTag& InputTag){ return InputTag.MatchesTagExact(FAuraGameplayTags::TAG_InputTag_LMB); }
	void ShiftPressed() { bShiftKeyDown = true; }
	void ShiftReleased() { bShiftKeyDown = false; }

	void Move(const struct FInputActionValue& InputActionValue);
	void CursorTrace();
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void SetAutoRunSpline();
	void MoveToHitPoint();
	void AutoRunToDestination();
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	FHitResult CursorHit;
	bool bShiftKeyDown = false;

	//Target Variables
	TScriptInterface<ITargetInterface> LastTargetActor;
	TScriptInterface<ITargetInterface> CurrentTargetActor;

	//Movement Variables
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
};
