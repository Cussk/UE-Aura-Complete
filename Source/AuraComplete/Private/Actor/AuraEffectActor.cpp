// Copyright Cuss Programming


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Basic root component as generic as it gets
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

/**
 * Boilerplate to apply the actors designated effect to the TargetActor (Pawn or Actor)
 * 
 * @param TargetActor Actor to apply the effect to
 * @param GameplayEffectClass Specific Gameplay Effect to be applied
 * @param bDestroyActor Should destroy this actor or not
 */
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass, const bool bDestroyActor)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAbilitySystemComponent == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// Track infinite effects that can be removed
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle, TargetAbilitySystemComponent);
	}

	if (bDestroyActor)
	{
		Destroy();
	}
}

/*
 * Apply effect when this Actor's collision component is overlapping with the Target
 */
void AAuraEffectActor::OnOverlap(AActor* TargetActor, const bool bDestroyActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass, bDestroyActor);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass, bDestroyActor);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass, bDestroyActor);
	}
}

/*
 * Apply effect when this Actor's collision component stops overlapping with the Target
 * If is an infinite effect with a Removal Policy of RemoveOnEndOverlap removes the Gameplay Effect
 */
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor, const bool bDestroyActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass, bDestroyActor);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass, bDestroyActor);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass, bDestroyActor);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveGameplayEffect(TargetActor);
	}
}

/*
 * Iterates through map of infinite gameplay effects that can be removed and removes effect where necessary 
 */
void AAuraEffectActor::RemoveGameplayEffect(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetAbilitySystemComponent)) return;

	for (auto Iterator = ActiveEffectHandles.CreateIterator(); Iterator; ++Iterator)
	{
		if (Iterator.Value() == TargetAbilitySystemComponent)
		{
			TargetAbilitySystemComponent->RemoveActiveGameplayEffect(Iterator.Key(), 1);
			Iterator.RemoveCurrent(); // safe removal during iteration
		}
	}
}


