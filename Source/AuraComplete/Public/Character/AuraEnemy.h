// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/TargetInterface.h"
#include "AuraEnemy.generated.h"

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

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Character Class Defaults")
	int32 Level = 1;
};
