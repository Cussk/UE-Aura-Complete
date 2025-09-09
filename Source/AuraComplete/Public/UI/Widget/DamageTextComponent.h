// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * A widget component used to display floating damage numbers in the world.
 * 
 * Exposes a Blueprint event (SetDamageText) so designers can control how
 * the damage value is visually presented (e.g., text style, animation).
 */
UCLASS()
class AURACOMPLETE_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage);
};
