// Copyright Cuss Programming


#include "UI/WidgetController/AuraWidgetController.h"

/**
 * Sets parameters Widget Controllers need to define callback logic, initialized from FWidgetControllerParameters struct
 */
void UAuraWidgetController::SetWidgetControllerParameters(const FWidgetControllerParameters& WidgetControllerParameters)
{
	PlayerController = WidgetControllerParameters.PlayerController;
	PlayerState = WidgetControllerParameters.PlayerState;
	AbilitySystemComponent = WidgetControllerParameters.AbilitySystemComponent;
	AttributeSet = WidgetControllerParameters.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
	
}
