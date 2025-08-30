// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Base character class for all Players
 * Top level for all Player related systems
 * All pertinent character components will be attached here
 */
UCLASS()
class AURACOMPLETE_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* Combat Interface */
	virtual int32 GetCharacterLevel() override;

protected:
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> CameraActor;

	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

private:
	void SetupTopDownCamera();
	void RotatePlayerToMovement();
	
};
