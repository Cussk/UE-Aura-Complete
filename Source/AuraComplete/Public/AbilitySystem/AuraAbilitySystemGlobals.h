// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * Holds global data for the gameplay ability system.
 */
UCLASS()
class AURACOMPLETE_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

	// Damage Related Curves
	inline static const FName ArmorPenetrationCurve = TEXT("ArmorPenetration");
	inline static const FName EffectiveArmorCurve   = TEXT("EffectiveArmor");
	inline static const FName CriticalHitResistanceCurve = TEXT("CriticalHitResistance");

	// Tags
	inline static const FName EnemyTag = TEXT("Enemy");
	inline static const FName PlayerTag = TEXT("Player");

	//Blackboard Variables
	inline static const FName BB_HitReacting = TEXT("bHitReacting");
	inline static const FName BB_RangedAttacker = TEXT("bRangedAttacker");
	inline static const FName BB_Dead = TEXT("bDead");
};
