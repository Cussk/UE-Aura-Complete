// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

/**
 * Central repository of native gameplay tags.
 * Add higher level tags here, define more specific instances in Data Tables in Editor
 */
namespace FMyGameplayTags
{
	// -----------------------------
	// Parent Tags
	// -----------------------------
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message);
	

	// -----------------------------
	// Attribute Sub Tags
	// -----------------------------
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary);	

};
