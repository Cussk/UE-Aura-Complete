// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURACOMPLETE_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

	// Damage Related Curves
	inline static const FName ArmorPenetration = TEXT("ArmorPenetration");
	inline static const FName EffectiveArmor   = TEXT("EffectiveArmor");
	inline static const FName CriticalHitResistance = TEXT("CriticalHitResistance");
};
