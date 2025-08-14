// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ITargetInterface;

/**
 * 
 */
UCLASS()
class AURACOMPLETE_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);
	void CursorTrace();

	TScriptInterface<ITargetInterface> LastActor;
	TScriptInterface<ITargetInterface> CurrentActor;
};
