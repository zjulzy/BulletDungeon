// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletDungeon/Character/AI/BdCharacterAI.h"
#include "BdSpawnPoint.generated.h"

UCLASS()
class BULLETDUNGEON_API ABdSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABdSpawnPoint();
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddEnemyWeights, TSubclassOf<ABdCharacterAI>);
	FOnAddEnemyWeights OnAddEnemyWeights;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABdCharacterAI> EnemyClass;

	FTimerHandle SpawnHandler;

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	float SpawnInterval;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
