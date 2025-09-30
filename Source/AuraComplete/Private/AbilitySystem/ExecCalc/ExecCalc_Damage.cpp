// Copyright Cuss Programming


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemGlobals.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

/*
 * Defines the Capture Definitions for the relevant Damage Modifiers
 * Maps Gameplay Tag for each Modifier to its Capture Definition
 */
struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefinitions;

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);

		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);

		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Resistance_Arcane, ArcaneResistanceDef);
		TagsToCaptureDefinitions.Add(FAuraGameplayTags::TAG_Attributes_Resistance_Physical, PhysicalResistanceDef);
		
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
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);

	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

/*
 * Calculates the Damage Modifiers and manipulates final damge
 * Outputs final damage for GamePlay Effect to use to apply damage
 */
void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	DamageContext DamageContext = CreateDamageContext(ExecutionParams);

	ApplyResistances(ExecutionParams, DamageContext);
	ApplyBlockChance(ExecutionParams, DamageContext);
	ApplyArmor(ExecutionParams, DamageContext);
	ApplyCriticalHit(ExecutionParams, DamageContext);

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

	DamageContext.SourceEffectContextHandle = DamageContext.GameplayEffectSpec->GetContext();

	return DamageContext;
}

/*
 * Loop through and capture each Resistance on Target
 * Reduce damage by 1 percent per point of Resistance
 */
void UExecCalc_Damage::ApplyResistances(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	DamageContext& DamageContext)
{
	// Get Damage Set by Caller Magnitude for each DamageType tag
	for (const TTuple<FGameplayTag, FGameplayTag>& DamageTypeAndResistance : FAuraGameplayTags::DamageTypesToResistances)
	{
		const FGameplayTag DamageType = DamageTypeAndResistance.Key;
		const FGameplayTag ResistanceTag = DamageTypeAndResistance.Value;

		checkf(AuraDamageStatics().TagsToCaptureDefinitions.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString())
		const FGameplayEffectAttributeCaptureDefinition CaptureDefinition = AuraDamageStatics().TagsToCaptureDefinitions[ResistanceTag];

		float DamageTypeValue =  DamageContext.GameplayEffectSpec->GetSetByCallerMagnitude(DamageType, false);

		float ResistanceMagnitude = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDefinition, DamageContext.EvaluateParameters, ResistanceMagnitude);
		ResistanceMagnitude = FMath::Clamp(ResistanceMagnitude, 0.0f, 100.f);

		DamageTypeValue *= (100.f - ResistanceMagnitude) / 100.f;
		
		DamageContext.Damage += DamageTypeValue;
	}
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
	UAuraAbilitySystemLibrary::SetIsBlockedHit(DamageContext.SourceEffectContextHandle, bBlocked);
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
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationsCoefficients->FindCurve(UAuraAbilitySystemGlobals::ArmorPenetrationCurve, FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(DamageContext.SourceCombatInterface->GetCharacterLevel());

	// Armor Penetration times the coefficient's value reduces TargetArmor 1 percent
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationsCoefficients->FindCurve(UAuraAbilitySystemGlobals::EffectiveArmorCurve, FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(DamageContext.TargetCombatInterface->GetCharacterLevel()); 

	// Effective Armor times the coefficient's value reduces damage by 1 percent
	DamageContext.Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;
}

/*
 * Capture CriticalHitResistance on Target and CriticalHitChance on Source, and determine remaining Critical Chance
 * If hits capture CriticalHitDamage and calculate new damage value 
 */
void UExecCalc_Damage::ApplyCriticalHit(const FGameplayEffectCustomExecutionParameters& ExecutionParams, DamageContext& DamageContext)
{
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, DamageContext.EvaluateParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(0.0f, SourceCriticalHitChance);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, DamageContext.EvaluateParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(0.0f, TargetCriticalHitResistance);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(DamageContext.SourceAvatar);
	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationsCoefficients->FindCurve(UAuraAbilitySystemGlobals::CriticalHitResistanceCurve, FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(DamageContext.TargetCombatInterface->GetCharacterLevel());

	// Critical Hit Resistance reduces Critical Hit Chance by a certain percentage
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;
	if (!bCriticalHit) return;

	UAuraAbilitySystemLibrary::SetIsCriticalHit(DamageContext.SourceEffectContextHandle, bCriticalHit);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, DamageContext.EvaluateParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(0.0f, SourceCriticalHitDamage);

	// Critical Hit doubles damage plus Source's Critical Hit Damage value
	DamageContext.Damage += DamageContext.Damage + SourceCriticalHitDamage;
}

