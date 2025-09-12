// Copyright Cuss Programming

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

/**
 * Binds BP Widgets to the delegate, event subscribed to in Blueprint Editor
 */
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	check(AttributeInformation)
	for (auto& TagAndAttribute : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TagAndAttribute.Value()).AddLambda(
			[this, TagAndAttribute](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(TagAndAttribute.Key, TagAndAttribute.Value());
			});
	}
}

/**
 * Fires the initial call for Attribute Info on widget creation
 */
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	check(AttributeInformation)
	for (auto& TagAndAttribute : AuraAttributeSet->TagsToAttributes)
	{
		BroadcastAttributeInfo(TagAndAttribute.Key, TagAndAttribute.Value());
	}
}

/**
 * Gets an FAuraAttributeInfo Struct and sets its current numeric value
 * Broadcasts the struct to the widgets that contain the matching AttributeTag
 */
void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInformation->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
