// Copyright Cuss Programming


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetController<UOverlayWidgetController>(WorldContextObject, &AAuraHUD::GetOverlayWidgetController);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetController<UAttributeMenuWidgetController>(WorldContextObject, &AAuraHUD::GetAttributeMenuWidgetController);
}

