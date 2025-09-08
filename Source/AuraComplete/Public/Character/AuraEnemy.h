// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/TargetInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * Base character class for all NPC enemies
 * Blueprint versions created for enemy types
 */
UCLASS()
class AURACOMPLETE_API AAuraEnemy : public AAuraCharacterBase, public ITargetInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	/* Target Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	/* Combat Interface */
	virtual int32 GetCharacterLevel() override;

	UPROPERTY(BlueprintAssignable)
	FOnFloatAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnFloatAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
