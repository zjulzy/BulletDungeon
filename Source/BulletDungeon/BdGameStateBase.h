// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Character/BdCharacterBase.h"
#include "GameFramework/GameStateBase.h"
#include "BdGameStateBase.generated.h"

/**
 * 
 */

// 关卡安排通关条件的数据表
USTRUCT(BlueprintType)
struct FLevelGoalTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLevelGoalTableRow()
	{
	};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BulletDungeon")
	int32 EnemyBaseNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BulletDungeon")
	int32 EnemySkeletonNum;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Outpost|LevelGoal")
	// FName Name;
	//
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Outpost|LevelGoal")
	// uint8 Type;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FonFinishedLevelGoal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFinishGoal,TSubclassOf<UObject>,GoalClass,int,Num);

UCLASS()
class BULLETDUNGEON_API ABdGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	FOnFinishGoal OnFinishGoal;
	
	ABdGameStateBase();
	TSubclassOf<ABdCharacterAI> EnemyBaseClass;
	TSubclassOf<ABdCharacterAI> EnemySkeletonClass;

	UFUNCTION(BlueprintCallable)
	void GetUnfinishedGoal(TMap<TSubclassOf<UObject>, int>& result);

	UFUNCTION(BlueprintCallable)
	void ResetGoal(FName LevelName);

	UFUNCTION(BlueprintCallable)
	void FinishGoal(TSubclassOf<UObject> GoalClass, int Num);

	UFUNCTION(BlueprintCallable)
	void OnEnemyKilled(TSubclassOf<ABdCharacterAI> EnemyClass);

	FonFinishedLevelGoal OnFinishedLevelGoal;

	UFUNCTION(BlueprintCallable)
	void GetCurrentEnemies(TMap<TSubclassOf<ABdCharacterAI>, int>& result);

	UFUNCTION(BlueprintCallable)
	void OnReduceEnemy(TSubclassOf<ABdCharacterAI> EnemyClass);

	UFUNCTION(BlueprintCallable)
	void OnAddEnemy(TSubclassOf<ABdCharacterAI> EnemyClass);

	UFUNCTION(BlueprintCallable)
	float GetCurrentWeights();

protected:
	UPROPERTY(BlueprintReadWrite)
	TMap<TSubclassOf<ABdCharacterAI>, int> CurrentEnemies;

	UPROPERTY(BlueprintReadWrite)
	float CurrentWeights;

	UPROPERTY(BlueprintReadWrite)
	TMap<TSubclassOf<UObject>, int> UnfinishedGoal;
	
};
