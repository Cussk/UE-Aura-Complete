// Copyright Cuss Programming

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * AbilityTask that gathers targeting data based on the player's mouse cursor.
 * 
 * This task handles both local and remote cases:
 * - Locally controlled players send cursor hit data to the server.
 * - Remotely controlled players wait for replicated data from the client.
 * 
 * Provides a multicast delegate (ValidData) that broadcasts when valid target
 * data has been captured, making it usable in both C++ and Blueprints.
 */
UCLASS()
class AURACOMPLETE_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = true))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:

	virtual void Activate() override;
	void SendMouseCursorData() const;
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) const;
	FHitResult GetCursorHit() const;
};
