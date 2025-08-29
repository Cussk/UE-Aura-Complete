// Copyright Cuss Programming


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParameters& WidgetControllerParameters)
{
	return GetWidgetController(WidgetControllerParameters, OverlayWidgetController, OverlayWidgetControllerClass);
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParameters& WidgetControllerParameters)
{
	return GetWidgetController(WidgetControllerParameters, AbilityMenuWidgetController, AbilityMenuWidgetControllerClass);
}

/**
 * Creates the main HUD Overlay
 * Sets the Widget Controller, Binds Callbacks, and Adds onscreen
 */
void AAuraHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
                           UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"))
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParameters WidgetControllerParameters(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParameters);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}
