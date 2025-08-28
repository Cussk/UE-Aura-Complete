// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UOverlayWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParameters;
/**
 * 
 */
UCLASS()
class AURACOMPLETE_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
		
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParameters& WidgetControllerParameters);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParameters& WidgetControllerParameters);

	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);

private:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AbilityMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AbilityMenuWidgetControllerClass;

	template <class T>
	T* GetWidgetController(const FWidgetControllerParameters& WidgetControllerParameters, TObjectPtr<T>& AuraWidgetController, TSubclassOf<T> AuraWidgetControllerClass);
};

template <class ControllerT>
ControllerT* AAuraHUD::GetWidgetController(const FWidgetControllerParameters& WidgetControllerParameters,
	TObjectPtr<ControllerT>& AuraWidgetController, TSubclassOf<ControllerT> AuraWidgetControllerClass)
{
	if (AuraWidgetController == nullptr)
	{
		AuraWidgetController = NewObject<ControllerT>(this, AuraWidgetControllerClass); //Pass AuraWidgetController pointer by reference so it can be assigned a new pointer
		AuraWidgetController->SetWidgetControllerParameters(WidgetControllerParameters);
		AuraWidgetController->BindCallbacksToDependencies();

		return AuraWidgetController;
	}

	return CastChecked<ControllerT>(AuraWidgetController);
}
