// Copyright Cuss Programming


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

/**
 * Applies damage to a target actor using the configured DamageEffectClass and DamageTypes.
 * Each DamageType is scaled by the current ability level and assigned as a SetByCaller magnitude.
 *
 * @param TargetActor - The actor that will receive the damage GameplayEffect.
 */
void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	const FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1);
	for (TTuple<FGameplayTag, FScalableFloat> TypeTagAndScalableFloat : DamageTypes)
	{
		const float ScaledDamage = TypeTagAndScalableFloat.Value.GetValueAtLevel(GetAbilityLevel()); 
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, TypeTagAndScalableFloat.Key, ScaledDamage);
	}

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));	
}
