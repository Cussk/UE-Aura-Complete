// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Controller.h"
#include "AuraPlayerController.generated.h"

class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
class ITargetInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class AURACOMPLETE_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	void AutoRunToDestination();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	static bool IsLMB(const FGameplayTag& InputTag){ return InputTag.MatchesTagExact(FAuraGameplayTags::TAG_InputTag_LMB); }

	void Move(const struct FInputActionValue& InputActionValue);
	void CursorTrace();
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void SetAutoRunSpline();
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void MoveToHitPoint();
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	FHitResult CursorHit;

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
