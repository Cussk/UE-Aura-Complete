// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UAnimMontage;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface attached to any Pawn that can be involved in Combat
 */
class AURACOMPLETE_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetCharacterLevel();
	virtual void Die() = 0;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();
};
