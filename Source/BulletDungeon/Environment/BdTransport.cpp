// Fill out your copyright notice in the Description page of Project Settings.


#include "BdTransport.h"

// Sets default values
ABdTransport::ABdTransport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = BaseMeshComponent;
}

// Called when the game starts or when spawned
void ABdTransport::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABdTransport::TravelToNewLevel_Implementation(const FString& TargetLevel, APlayerController* Controller)
{
	AGameStateBase* GS  =GetWorld()->GetGameState();
}

// Called every frame
void ABdTransport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

