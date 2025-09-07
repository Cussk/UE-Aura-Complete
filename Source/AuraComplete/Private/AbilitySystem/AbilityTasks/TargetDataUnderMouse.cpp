// Copyright Cuss Programming


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"

/**
 * Factory method that creates and initializes a new instance of the UTargetDataUnderMouse task.
 * 
 * This follows the Factory Pattern commonly used in Unreal's AbilityTask system,
 * where static creation methods wrap object instantiation and initialization.
 * 
 * @param OwningAbility - The gameplay ability that owns this task.
 * @return A new UTargetDataUnderMouse task bound to the given ability.
 */
UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObject = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObject;
}

/**
 * Called when the task is activated.
 * 
 * - If locally controlled: immediately sends target data under the mouse cursor to the server.
 * - If remotely controlled: registers a delegate to wait for replicated target data from the client.
 */
void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey PredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, PredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, PredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

/**
 * Collects mouse cursor hit data and sends it to the server for replication.
 * 
 * - Wraps the call in a scoped prediction window for proper prediction handling.
 * - Builds a target data handle containing the hit result under the cursor.
 * - Sends the data to the server via ServerSetReplicatedTargetData().
 * - Broadcasts the data to any bound delegates if broadcasting is enabled.
 */
void UTargetDataUnderMouse::SendMouseCursorData() const
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data -> HitResult = GetCursorHit();
	DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

/**
 * Callback executed when target data is received from a remote client.
 * 
 * - Consumes the replicated target data for the current ability and prediction key.
 * - Broadcasts the received data to any bound delegates if broadcasting is enabled.
 * 
 * @param DataHandle - The replicated target data received from the client.
 * @param ActivationTag - Gameplay tag associated with the activation (unused here).
 */
void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) const
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

/**
 * Retrieves the hit result under the local player's mouse cursor.
 * 
 * - If using a custom AuraPlayerController, calls its GetCursorHit() method.
 * - Otherwise, falls back to the default engine GetHitResultUnderCursor().
 * 
 * @return The FHitResult representing what the mouse cursor is currently over.
 */
FHitResult UTargetDataUnderMouse::GetCursorHit() const
{
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(PlayerController);
	FHitResult CursorHitResult;
	if (AuraPlayerController)
	{
		CursorHitResult = AuraPlayerController->GetCursorHit();
	}
	else
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
	}

	return CursorHitResult;
}
