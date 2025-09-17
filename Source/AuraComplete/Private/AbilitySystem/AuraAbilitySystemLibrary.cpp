// Copyright Cuss Programming

#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "Engine/OverlapResult.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/CombatInterface.h"

/**
 * Retrieves the Overlay Widget Controller from the current HUD.
 *
 * @param WorldContextObject - Context object used to resolve the world.
 * @return Pointer to the Overlay Widget Controller.
 */
UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetController<UOverlayWidgetController>(WorldContextObject, &AAuraHUD::GetOverlayWidgetController);
}

/**
 * Retrieves the Attribute Menu Widget Controller from the current HUD.
 *
 * @param WorldContextObject - Context object used to resolve the world.
 * @return Pointer to the Attribute Menu Widget Controller.
 */
UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetController<UAttributeMenuWidgetController>(WorldContextObject, &AAuraHUD::GetAttributeMenuWidgetController);
}

/**
 * Initializes a character's default attributes (Primary, Secondary, and Vital) 
 * using Gameplay Effects defined in the CharacterClassInfo.
 *
 * @param WorldContextObject - Context object used to access the game world.
 * @param CharacterClass - The class type of the character (e.g., Warrior, Mage).
 * @param Level - Character level, used for scaling attribute values.
 * @param AbilitySystemComponent - The ASC that will receive the attribute Gameplay Effects.
 */
void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, const ECharacterClass CharacterClass, const float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	const AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo =  GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = AbilitySystemComponent->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = AbilitySystemComponent->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = AbilitySystemComponent->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

/**
 * Grants starting abilities to a character based on CharacterClassInfo.
 * Adds both common abilities (shared across all classes) and class-specific starting abilities.
 *
 * @param WorldContextObject - Context object used to resolve the game world.
 * @param AbilitySystemComponent - The ASC that will be given the abilities.
 * @param CharacterClass - The class type determining which abilities to grant.
 */
void UAuraAbilitySystemLibrary::GiveStartingAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo) return;
	
	for (const TSubclassOf AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	
	const FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf AbilityClass : DefaultInfo.StartingAbilities)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(AbilitySystemComponent->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetCharacterLevel());
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

/**
 * Retrieves the CharacterClassInfo asset from the current game mode.
 *
 * @param WorldContextObject - Context object used to resolve the game world.
 * @return Pointer to the CharacterClassInfo data asset, or nullptr if not found.
 */
UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!AuraGameMode) return nullptr;
	return AuraGameMode->CharacterClassInformation;
}

/**
 * Checks if the given GameplayEffectContext indicates a blocked hit.
 *
 * @param EffectContextHandle - Handle to the Gameplay Effect context.
 * @return True if the hit was blocked, false otherwise.
 */
bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraGameplayContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraGameplayContext->IsBlockedHit();
	}

	return false;
}

/**
 * Checks if the given GameplayEffectContext indicates a critical hit.
 *
 * @param EffectContextHandle - Handle to the Gameplay Effect context.
 * @return True if the hit was critical, false otherwise.
 */
bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraGameplayContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraGameplayContext->IsCriticalHit();
	}

	return false;
}

/**
 * Sets the blocked hit flag on a GameplayEffectContext.
 *
 * @param EffectContextHandle - Handle to the Gameplay Effect context (modifiable).
 * @param bInIsBlockedHit - Whether the hit should be marked as blocked.
 */
void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsBlockedHit)
{
	if (FAuraGameplayEffectContext* AuraGameplayEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraGameplayEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

/**
 * Sets the critical hit flag on a GameplayEffectContext.
 *
 * @param EffectContextHandle - Handle to the Gameplay Effect context (modifiable).
 * @param bInIsCriticalHit - Whether the hit should be marked as critical.
 */
void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsCriticalHit)
{
	if (FAuraGameplayEffectContext* AuraGameplayEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraGameplayEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

/**
 * Finds all living actors within a sphere radius who implement the CombatInterface.
 *
 * @param WorldContextObject - Context object used to resolve the world.
 * @param OutOverlappingActors - Array to populate with found actors.
 * @param ActorsToIgnore - List of actors to ignore during overlap check.
 * @param Radius - Radius of the search sphere.
 * @param SphereOrigin - Center position of the search sphere.
 */
void UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
	const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
			FCollisionShape::MakeSphere(Radius), SphereParams);

		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(Overlap.GetActor());
			}
		}
	}
}
