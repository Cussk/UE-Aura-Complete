// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

class ICombatInterface;

struct DamageContext
{
	const UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	const UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;

	AActor* SourceAvatar = nullptr;
	AActor* TargetAvatar = nullptr;

	ICombatInterface* SourceCombatInterface = nullptr;
	ICombatInterface* TargetCombatInterface = nullptr;

	const FGameplayEffectSpec* GameplayEffectSpec = nullptr;
	FGameplayEffectContextHandle SourceEffectContextHandle;

	const FGameplayTagContainer* SourceTags = nullptr;
	const FGameplayTagContainer* TargetTags = nullptr;

	FAggregatorEvaluateParameters EvaluateParameters;
	float Damage = 0.f;
};

/**
 * 
 */
UCLASS()
class AURACOMPLETE_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_Damage();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	static DamageContext CreateDamageContext(const FGameplayEffectCustomExecutionParameters& ExecutionParams);
	static void ApplyResistances(const FGameplayEffectCustomExecutionParameters& ExecutionParams, DamageContext& DamageContext);
	static void ApplyBlockChance(const FGameplayEffectCustomExecutionParameters& ExecutionParams, DamageContext& DamageContext);
	static void ApplyArmor(const FGameplayEffectCustomExecutionParameters& ExecutionParams, DamageContext& DamageContext);
	static void ApplyCriticalHit(const FGameplayEffectCustomExecutionParameters& ExecutionParams, DamageContext& DamageContext);
};
