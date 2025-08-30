// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * Base project class for Gameplay Abilities
 * Set any initial InputTags in Blueprint children
 */
UCLASS()
class AURACOMPLETE_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartingInputTag;
};
