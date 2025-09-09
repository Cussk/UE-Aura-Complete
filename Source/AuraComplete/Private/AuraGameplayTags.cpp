// Copyright Cuss Programming


#include "AuraGameplayTags.h"

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

//Input Tags
UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_LMB, "InputTag.LMB", "Left Mouse Button Input Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_RMB, "InputTag.RMB", "Right Mouse Button Input Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_1, "InputTag.1", "Key 1 Input Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_2, "InputTag.2", "Key 2 Input Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_3, "InputTag.3", "Key 3 Input Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_InputTag_4, "InputTag.4", "Key 4 Input Tag");


UE_DEFINE_GAMEPLAY_TAG_COMMENT(FAuraGameplayTags::TAG_Damage, "Damage", "Damage dealt");