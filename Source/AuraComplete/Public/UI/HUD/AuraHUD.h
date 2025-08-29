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
 * Main HUD class
 * Blueprint version allows for creation of other blueprint on it and setting of Widget Controller classes
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

	template <class T>
	T* GetWidgetController(const FWidgetControllerParameters& WidgetControllerParameters, TObjectPtr<T>& AuraWidgetController, TSubclassOf<T> AuraWidgetControllerClass);

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
};

/**
 *	Generic WidgetController pointer getter, creates or casts to any child of AuraWidgetController
 * 
 * @tparam ControllerT Controller child to be returned
 * @param WidgetControllerParameters Struct const reference  providing Parameters controller needs to be initialized
 * @param AuraWidgetController Generic AuraWidgetController pointer reference can be any child of AUraWidgetController,
 * sets desired child version in AuraHUD after creating for easier Getting
 * @param AuraWidgetControllerClass Generic controller class, can be any child class of AuraWidgetController
 * @return Desired pointer to child of AuraWidgetController
 */
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
