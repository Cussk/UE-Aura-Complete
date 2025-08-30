// Copyright Cuss Programming


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

/*
 * Sets pertinent Information for the Ability Actor Info 
 */
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);
}

/**
 * Adds Gameplay Abilities to Character classes
 * 
 * @param StartingAbilities Array of Abilities granted to a basic level 1 Character
 */
void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartingAbilities)
{
	for (const TSubclassOf AbilityClass : StartingAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		const UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability);
		if (AuraGameplayAbility)
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraGameplayAbility->StartingInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

/*
 * Marks matching ability's input as pressed.
 * - Sets Spec.InputPressed = true
 * - If ability not active, attempts to activate it
 * => Enables tap-to-activate or hold-to-channel behavior
 */
void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

/*
 * Marks matching ability's input as released.
 * - Sets Spec.InputPressed = false
 * - Active abilities can end themselves when input is released
 * => Enables charge, channel, or cancel-on-release behavior
 */
void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

/*
 * Client RPC called when a GameplayEffect is applied.
 * - Extracts all asset tags from the effect spec
 * - Broadcasts them via EffectAssetTags delegate for UI/logic listeners
 */
void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
