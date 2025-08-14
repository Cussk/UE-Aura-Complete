// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class AURACOMPLETE_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
AAuraPlayerController();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;
};
