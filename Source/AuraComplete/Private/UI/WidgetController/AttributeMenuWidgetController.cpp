// Copyright Cuss Programming

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);

	check(AttributeInformation)

	FAuraAttributeInfo Info = AttributeInformation->FindAttributeInfoForTag(FAuraGameplayTags::TAG_Attributes_Primary_Strength);
	Info.AttributeValue= AuraAttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
