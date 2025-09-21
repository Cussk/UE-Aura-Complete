// Copyright Cuss Programming


#include "AuraGameplayTags.h"
#include "GameplayTagContainer.h" 

namespace FAuraGameplayTags
{
	// Parent Tags
	UE_DEFINE_GAMEPLAY_TAG(FAuraGameplayTags::TAG_Attributes, "Attributes");
	UE_DEFINE_GAMEPLAY_TAG(FAuraGameplayTags::TAG_Message, "Message");

	// Primary Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Primary_Strength, "Attributes.Primary.Strength", "Increases physical damage");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence", "Increases magical damage and mana");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Primary_Resilience, "Attributes.Primary.Resilience", "Increases armor and armor penetration");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Primary_Vigor, "Attributes.Primary.Vigor", "Increases health");
 
	// Secondary Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_Armor, "Attributes.Secondary.Armor", "Reduces damage taken, improves Block Chance");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration", "Ignores percentage of enemy Armor, increases Critical Hit Chance");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_BlockChance, "Attributes.Secondary.BlockChance", "Chance to cut incoming damage in half");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance", "Chance to double damage plus critical hit bonus");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_CriticalHitDamage, "Attributes.Secondary.CriticalHitDamage", "Bonus damage added when a critical hit is scored");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_CriticalHitResistance, "Attributes.Secondary.CriticalHitResistance", "Reduces critical hit chance of attacking enemies");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration", "Amount of Health regenerated every 1 second");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration", "Amount of Mana regenerated every 1 second");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth", "Total health character has");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana", "Total mana character has");
 
	// Vital Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Vitals_Health, "Attributes.Vitals.Health", "Amount of damage a player can take before death");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Vitals_Mana, "Attributes.Vitals.Mana", "Used for casting spells and abilities");

	// Resistance Attributes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Resistance_Fire, "Attributes.Resistance.Fire", "Reduces Fire damage taken");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Resistance_Lightning, "Attributes.Resistance.Lightning", "Reduces Lightning damage taken");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Resistance_Arcane, "Attributes.Resistance.Arcane", "Reduces Arcane damage taken");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Attributes_Resistance_Physical, "Attributes.Resistance.Physical", "Reduces Physical damage taken");

	//Input Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_LMB, "InputTag.LMB", "Left Mouse Button Input Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_RMB, "InputTag.RMB", "Right Mouse Button Input Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_1, "InputTag.1", "Key 1 Input Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_2, "InputTag.2", "Key 2 Input Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_3, "InputTag.3", "Key 3 Input Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_4, "InputTag.4", "Key 4 Input Tag");

	// Damage Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Damage, "Damage", "Damage");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Damage_Fire, "Damage.Fire", "Fire Damage Type");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Damage_Lightning, "Damage.Lightning", "Lightning Damage Type");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Damage_Arcane, "Damage.Arcane", "Arcane Damage Type");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Damage_Physical, "Damage.Physical", "Physical Damage Type");

	// Abilities Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Abilities_Attack, "Abilities.Attack", "Attack Ability Tag");

	//Combat Socket Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_CombatSocket_Weapon, "CombatSocket.Weapon", "Weapon Socket Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_CombatSocket_RightHand, "CombatSocket.RightHand", "RightHand Socket Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_CombatSocket_LeftHand, "CombatSocket.LeftHand", "LeftHand Socket Tag");

	//Montage Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Montage_Attack_1, "Montage.Attack.1", "Attack 1");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Montage_Attack_2, "Montage.Attack.2", "Attack 2");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Montage_Attack_3, "Montage.Attack.3", "Attack 3");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Montage_Attack_4, "Montage.Attack.4", "Attack 4");

	//Anim Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Effects_HitReact, "Effects.HitReact", "Tag granted when hit reacted");

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances =
	{
		{TAG_Damage_Fire, TAG_Attributes_Resistance_Fire},
		{TAG_Damage_Lightning, TAG_Attributes_Resistance_Lightning},
		{TAG_Damage_Arcane, TAG_Attributes_Resistance_Arcane},
		{TAG_Damage_Physical, TAG_Attributes_Resistance_Physical}
	};
}