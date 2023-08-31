// Fill out your copyright notice in the Description page of Project Settings.


#include "BdGameStateBase.h"

#include "BulletDungeonGameModeBase.h"
#include "Character/AI/BdCharacterAI.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ABdGameStateBase::ABdGameStateBase()
{
	CurrentWeights = 0;

	// 初始化所有敌人的class
	EnemyBaseClass = ConstructorHelpers::FClassFinder<ABdCharacterAI>(
		TEXT("/Script/Engine.Blueprint'/Game/Characters/AI/BP_DemoEnemy.BP_DemoEnemy_C'")).Class;
	OnFinishGoal.AddDynamic(this, &ABdGameStateBase::FinishGoal);
}

void ABdGameStateBase::GetUnfinishedGoal(TMap<TSubclassOf<UObject>, int>& result)
{
	result = UnfinishedGoal;
}

void ABdGameStateBase::ResetGoal(FName LevelName)
{
	//通过读取数据表和难度设置本关卡的goal
	ABulletDungeonGameModeBase* GM = Cast<ABulletDungeonGameModeBase>(GetWorld()->GetAuthGameMode());
	UnfinishedGoal.Empty();
	int Difficulty = GM->GetDifficulty();

	//通过datatable初始化unfinishedgoals
	UDataTable* const LevelGoalDataTable = LoadObject<UDataTable>(
		this, TEXT("/Script/Engine.DataTable'/Game/Maps/Data/DT_LevelGoals.DT_LevelGoals'"));
	ensure(LevelGoalDataTable);
	if (LevelGoalDataTable)
	{
		FLevelGoalTableRow* Row = LevelGoalDataTable->FindRow<FLevelGoalTableRow>(LevelName,TEXT("name"));
		if (Row)
		{
			UKismetSystemLibrary::PrintString(this,TEXT("find row"));
			if (Row->EnemyBaseNum > 0)
			{
				if (EnemyBaseClass.GetDefaultObject()->GetWeight() <= Difficulty)
				{
					UnfinishedGoal.Add(EnemyBaseClass, Row->EnemyBaseNum * Difficulty);
				}
			}
		}
	}
}

void ABdGameStateBase::FinishGoal(TSubclassOf<UObject> GoalClass, int Num)
{
	int* number = UnfinishedGoal.Find(GoalClass);
	if (number)
	{
		(*number) -= Num;
	}
	else
	{
		return;
	}
	for (auto i = UnfinishedGoal.CreateIterator(); i; ++i)
	{
		if (i.Value() != 0)return;
	}
	OnFinishedLevelGoal.Broadcast();
}

void ABdGameStateBase::OnEnemyKilled(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	OnFinishGoal.Broadcast(EnemyClass, 1);
}


void ABdGameStateBase::GetCurrentEnemies(TMap<TSubclassOf<ABdCharacterAI>, int>& result)
{
	result = CurrentEnemies;
}

void ABdGameStateBase::OnReduceEnemy(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	//减少敌人weight
	CurrentWeights -= EnemyClass.GetDefaultObject()->GetWeight();
	CurrentEnemies[EnemyClass]--;
}

void ABdGameStateBase::OnAddEnemy(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	//增加敌人weight
	CurrentWeights += EnemyClass.GetDefaultObject()->GetWeight();
	if (CurrentEnemies.Contains(EnemyClass))
	{
		CurrentEnemies[EnemyClass]++;
	}
	else
	{
		CurrentEnemies.Add(EnemyClass, 1);
	}
}

float ABdGameStateBase::GetCurrentWeights()
{
	return CurrentWeights;
}
