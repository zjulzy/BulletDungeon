// Fill out your copyright notice in the Description page of Project Settings.


#include "BdEquipment.h"

#include "BdInteractionInterface.h"

// Sets default values
ABdEquipment::ABdEquipment()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent = SkeletalMeshComponent;
}

bool ABdEquipment::CanBeInteracted_Implementation()
{
	IBdInteractionInterface::CanBeInteracted_Implementation();
	if (!Equiper)
	{
		return true;
	}
	return false;
}

void ABdEquipment::SetEquiper(APawn* NewEquiper)
{
	Equiper = NewEquiper;
}

void ABdEquipment::Use_Implementation()
{
}

void ABdEquipment::Interacted_Implementation(APawn* InstigatorPawn)
{
	IBdInteractionInterface::Interacted_Implementation(InstigatorPawn);
}

// Called when the game starts or when spawned
void ABdEquipment::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABdEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
