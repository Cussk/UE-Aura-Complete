// Copyright Cuss Programming


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

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

