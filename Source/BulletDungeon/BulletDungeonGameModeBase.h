// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Environment/BdTransport.h"
#include "GameFramework/GameModeBase.h"
#include "BulletDungeonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API ABulletDungeonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABulletDungeonGameModeBase();
	virtual void BeginPlay() override;
	
	
	UFUNCTION(BlueprintCallable)
	FVector GetNextLevelLocation();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void LoadAndTravelNewLevel();

	UFUNCTION(BlueprintCallable)
	bool CanSpawnEnemy(TSubclassOf<ABdCharacterAI> EnemyClass);
	
	UFUNCTION(BlueprintCallable)
	int GetDifficulty();

	UFUNCTION(BlueprintCallable)
	void LevelFinished();
protected:
	UPROPERTY(EditAnywhere)
	int MaxLevel;

	UPROPERTY(EditAnywhere)
	TArray<FName>LevelNames;

	UPROPERTY(EditAnywhere,Category="Outpost")
	TSubclassOf<ABdTransport> TransportClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ULevelStreaming> CurrentLevel;

	FVector CurrentLevelLocation;
	int LevelID;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Difficulty;

	
	
};
