// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * Static library of functions accessible in Blueprints specific to this project 
 */
UCLASS()
class AURACOMPLETE_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

private:

	template <typename T>
	static T* GetWidgetController(const UObject* WorldContextObject, T* (AAuraHUD::*Getter)(const FWidgetControllerParameters&));
	
};

/**
 * Generic function to get any AuraWidgetContoller based on the widget getter passed in
 * 
 * @tparam T Pointer to desired AUraWidgetController child
 * @param WorldContextObject UObject pointer to an object in the current level for context
 * @param Getter Pointer to a Getter function in AAuraHUD class for AuraWidgetController children
 * @return Pointer to AuraWidgetController child
 */
template <typename T>
T* UAuraAbilitySystemLibrary::GetWidgetController(const UObject* WorldContextObject, T* (AAuraHUD::*Getter)(const FWidgetControllerParameters&) )
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = PlayerController->GetHUD<AAuraHUD>())
		{
			if (AAuraPlayerState* PlayerState = PlayerController->GetPlayerState<AAuraPlayerState>())
			{
				UAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
				UAttributeSet* AttributeSet = PlayerState->GetAttributeSet();
				const FWidgetControllerParameters Params(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
				return (AuraHUD->*Getter)(Params);
			}
		}
	}
	return nullptr;
}

