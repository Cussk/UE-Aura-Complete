// Copyright Cuss Programming


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParameters(const FWidgetControllerParameters& WidgetControllerParameters)
{
	PlayerController = WidgetControllerParameters.PlayerController;
	PlayerState = WidgetControllerParameters.PlayerState;
	AbilitySystemComponent = WidgetControllerParameters.AbilitySystemComponent;
	AttributeSet = WidgetControllerParameters.AttributeSet;
}
