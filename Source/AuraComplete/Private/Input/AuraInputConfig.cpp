// Copyright Cuss Programming


#include "Input/AuraInputConfig.h"

#include "InputAction.h"

/*
 * Checks Player owned abilities for matching input tags assigned to the ability
 */
const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound) const
{
	for (const FAuraInputAction& InputAction : AbilityInputActions)
	{
		if (InputAction.InputAction && InputAction.InputTag.MatchesTagExact(InputTag))
		{
			return InputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("InputAction not found for InputTag %s, on InputConfig %s"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
