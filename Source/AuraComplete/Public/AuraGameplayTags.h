// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

/**
 * Central repository of native gameplay tags.
 * Add higher level tags here, define more specific instances in Data Tables in Editor
 */
namespace FAuraGameplayTags
{
	// Parent Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message);
	
	// Primary
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Strength);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Intelligence);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Resilience);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Vigor);
 
	// Secondary
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
 
	// Vitals
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vitals_Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vitals_Mana);

};
