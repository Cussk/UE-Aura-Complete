// Copyright Cuss Programming


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

/**
 * Sends initial health and mana values on Widget creation
 */
void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributes->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributes->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributes->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	BindAttributeChangeCallbacks();
	BindMessageInfoCallback();
}

/**
 * Binds specific FGameplayAttribute to its corresponding on change delegate
 * Broadcasts new numeric values for Attribute to display in Widgets
 */
void UOverlayWidgetController::BindAttributeChangeCallbacks()
{
	const UAuraAttributeSet* AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);

	//Generic bind for attributes
	auto Bind = [this](const FGameplayAttribute& Attribute, auto& BroadcastDelegate)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute)
							  .AddLambda([&BroadcastDelegate](const FOnAttributeChangeData& Data)
							  {
								  BroadcastDelegate.Broadcast(Data.NewValue);
							  });
	};

	Bind(AuraAttributes->GetHealthAttribute(), OnHealthChanged);
	Bind(AuraAttributes->GetMaxHealthAttribute(), OnMaxHealthChanged);
	Bind(AuraAttributes->GetManaAttribute(), OnManaChanged);
	Bind(AuraAttributes->GetMaxManaAttribute(), OnMaxManaChanged);
}

/**
 * Loops through EffectAssetTags and binds a delegate if they have a Message parent tag
 * Broadcasts Row Info for message popup Widget
 */
void UOverlayWidgetController::BindMessageInfoCallback() const
{
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				if (Tag.MatchesTag(FAuraGameplayTags::TAG_Message))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				    MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}	
		});
}

