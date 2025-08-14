// Copyright Cuss Programming

#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletalMeshComponent");
	WeaponSkeletalMeshComponent->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}


