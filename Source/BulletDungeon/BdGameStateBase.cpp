// Fill out your copyright notice in the Description page of Project Settings.


#include "BdGameStateBase.h"

#include "BulletDungeonGameModeBase.h"
#include "Character/AI/BdCharacterAI.h"
#include "Kismet/KismetSystemLibrary.h"

ABdGameStateBase::ABdGameStateBase()
{
	CurrentWeights = 0;

	// 初始化所有敌人的class
	EnemyBaseClass = ConstructorHelpers::FClassFinder<ABdCharacterAI>(TEXT("/Script/Engine.Blueprint'/Game/Characters/AI/BP_DemoEnemy.BP_DemoEnemy_C'")).Class;
}

TMap<TSubclassOf<UObject>, int> ABdGameStateBase::GetUnfinishedGoal()
{
	return UnfinishedGoal;
}

void ABdGameStateBase::ResetGoal(FName LevelName)
{
	//通过读取数据表和难度设置本关卡的goal
	ABulletDungeonGameModeBase* GM = Cast<ABulletDungeonGameModeBase>(GetWorld()->GetAuthGameMode());
	Difficulty = GM->GetDifficulty();
	UnfinishedGoal.Empty();

	//通过datatable初始化unfinishedgoals
	UDataTable* const LevelGoalDataTable = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/Maps/Data/DT_LevelGoals.DT_LevelGoals'"));
	if(LevelGoalDataTable)
	{
		FLevelGoalTableRow* Row = LevelGoalDataTable->FindRow<FLevelGoalTableRow>(LevelName,TEXT("name"));
		if(Row)
		{
			UKismetSystemLibrary::PrintString(this,TEXT("find row"));
			if(Row->EnemyBaseNum>0)
			{
				UnfinishedGoal.Add(EnemyBaseClass,Row->EnemyBaseNum);
			}
		}
	}
}

bool ABdGameStateBase::FinishGoal(TSubclassOf<UObject> goal, int num)
{
	int* number = UnfinishedGoal.Find(goal);
	if(number)
	{
		(*number)-=num;
	}else
	{
		return false;
	}
	for(auto i = UnfinishedGoal.CreateIterator();i;++i)
	{
		if(i.Value()!=0)return true;
	}
	OnFinishedLevelGoal.Broadcast();
	return true;
}

void ABdGameStateBase::OnEnemyKilled(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	FinishGoal(EnemyClass,1);
}

TMap<TSubclassOf<ABdCharacterAI>, int> ABdGameStateBase::GetCurrentEnemies()
{
	return CurrentEnemies;
}

void ABdGameStateBase::OnReduceEnemy(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	//减少敌人weight
	CurrentWeights-=EnemyClass.GetDefaultObject()->GetWeight();
	CurrentEnemies[EnemyClass]--;
}

void ABdGameStateBase::OnAddEnemy(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	//增加敌人weight
	CurrentWeights+=EnemyClass.GetDefaultObject()->GetWeight();
	if(CurrentEnemies.Contains(EnemyClass))
	{
		CurrentEnemies[EnemyClass]++;
	}else
	{
		CurrentEnemies.Add(EnemyClass,1);
	}
}

float ABdGameStateBase::GetCurrentWeights()
{
	return CurrentWeights;
}
