// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

/**
 * Central repository of native gameplay tags.
 * Declare Macro here and Define macro with or without comment in .cpp
 */
namespace FAuraGameplayTags
{	
	// Parents
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message);
	
	// Primary Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Strength);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Intelligence);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Resilience);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Vigor);
 
	// Secondary Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_Armor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_ArmorPenetration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_BlockChance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_CriticalHitChance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_CriticalHitDamage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_CriticalHitResistance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_HealthRegeneration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_ManaRegeneration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_MaxHealth);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_MaxMana);
 
	// Vital Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vitals_Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vitals_Mana);

	// Resistance Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Resistance_Fire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Resistance_Lightning);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Resistance_Arcane);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Resistance_Physical);

	//Input Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_InputTag_LMB)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_InputTag_RMB)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_InputTag_1)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_InputTag_2)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_InputTag_3)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_InputTag_4)

	// Damage Type Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damage)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damage_Fire)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damage_Lightning)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damage_Arcane)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damage_Physical)

	//Abilities Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Abilities_Attack)

	//Combat Socket Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_CombatSocket_Weapon)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_CombatSocket_RightHand)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_CombatSocket_LeftHand)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_CombatSocket_Tail)

	//Montage Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Montage_Attack_1)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Montage_Attack_2)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Montage_Attack_3)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Montage_Attack_4)

	//Anim Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effects_HitReact)

	extern TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

};
