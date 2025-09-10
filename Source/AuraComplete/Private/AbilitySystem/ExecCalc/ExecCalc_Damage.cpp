// Copyright Cuss Programming


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraCurveNames.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}
void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	DamageContext DamageContext = CreateDamageContext(ExecutionParams);

	ApplyBlockChance(ExecutionParams, DamageContext);
	ApplyArmor(ExecutionParams, DamageContext);

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, DamageContext.Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

/*
 * Creates struct to hold relevant variables for damage execution calculation
 */
DamageContext UExecCalc_Damage::CreateDamageContext(const FGameplayEffectCustomExecutionParameters& ExecutionParams)
{
	DamageContext DamageContext;
	DamageContext.SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();
	DamageContext.TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();

	DamageContext.SourceAvatar = DamageContext.SourceAbilitySystemComponent ? DamageContext.SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	DamageContext.TargetAvatar = DamageContext.TargetAbilitySystemComponent ? DamageContext.TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	DamageContext.SourceCombatInterface = Cast<ICombatInterface>(DamageContext.SourceAvatar);
	DamageContext.TargetCombatInterface = Cast<ICombatInterface>(DamageContext.TargetAvatar);

	DamageContext.GameplayEffectSpec = &ExecutionParams.GetOwningSpec();

	DamageContext.SourceTags = DamageContext.GameplayEffectSpec->CapturedSourceTags.GetAggregatedTags();
	DamageContext.TargetTags = DamageContext.GameplayEffectSpec->CapturedTargetTags.GetAggregatedTags();

	DamageContext.EvaluateParameters.SourceTags = DamageContext.SourceTags;
	DamageContext.EvaluateParameters.TargetTags = DamageContext.TargetTags;

	// Get Damage Set by Caller Magnitude
	DamageContext.Damage = DamageContext.GameplayEffectSpec->GetSetByCallerMagnitude(FAuraGameplayTags::TAG_Damage);

	return DamageContext;
}

/*
 * Capture BlockChance on Target, and determine if there was a successful Block
 * If Blocked halve Damage
 */
void UExecCalc_Damage::ApplyBlockChance(const FGameplayEffectCustomExecutionParameters& ExecutionParams, DamageContext& DamageContext)
{
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, DamageContext.EvaluateParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.0f, TargetBlockChance);
	
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	DamageContext.Damage = bBlocked ? DamageContext.Damage / 2.f : DamageContext.Damage;
}

/*
 * Capture Armor on Target and ArmorPenetration on Source, and determine remaining Armor
 * ArmorPenetration ignores a percentage of the Target's Armor
 */
void UExecCalc_Damage::ApplyArmor(const FGameplayEffectCustomExecutionParameters& ExecutionParams, DamageContext& DamageContext)
{	
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, DamageContext.EvaluateParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.0f, TargetArmor);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, DamageContext.EvaluateParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.0f, SourceArmorPenetration);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(DamageContext.SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationsCoefficients->FindCurve(AuraCurveNames::ArmorPenetration, FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(DamageContext.SourceCombatInterface->GetCharacterLevel());

	// Armor Penetration times the coefficient's value reduces TargetArmor 1 percent
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationsCoefficients->FindCurve(AuraCurveNames::EffectiveArmor, FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(DamageContext.TargetCombatInterface->GetCharacterLevel()); 

	// Effective Armor times the coefficient's value reduces damage by 1 percent
	DamageContext.Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;
}

