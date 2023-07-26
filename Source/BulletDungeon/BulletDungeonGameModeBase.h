// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Environment/BdTransport.h"
#include "GameFramework/GameModeBase.h"
#include "BdGameStateBase.h"
#include "Character/BdCharacterHero.h"
#include "Environment/BdTransport.h"
#include "Player/BdPlayerController.h"
#include "Player/BdPlayerState.h"
#include "Character/AI/BdCharacterAI.h"
#include "BulletDungeonGameModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRefreshLevel);
UCLASS()
class BULLETDUNGEON_API ABulletDungeonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	//在进入新的关卡之后通知UI等进行刷新
	UPROPERTY(BlueprintCallable)
	FRefreshLevel RefreshLevel;
	
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

	UPROPERTY(EditAnywhere,Category="BulletDungeon")
	TSubclassOf<ABdTransport> TransportClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ULevelStreaming> CurrentLevel;

	UPROPERTY(BlueprintReadWrite)
	FVector CurrentLevelLocation;
	int LevelID;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Difficulty;

	
	
};
