// Copyright Cuss Programming


#include "AbilitySystem/AuraAbilitySystemGlobals.h"

#include "AuraAbilityTypes.h"
/*
 * Changes created GameplayEffectContext to project specific FAuraGameplayEffectContext
 */
FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
