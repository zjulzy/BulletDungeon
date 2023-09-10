// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletDungeon/Equipments/BdInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "BdTransport.generated.h"

UCLASS()
class BULLETDUNGEON_API ABdTransport : public AActor, public IBdInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABdTransport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMeshComponent;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TravelToNewLevel(const FString& TargetLevel, APlayerController* Controller);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
