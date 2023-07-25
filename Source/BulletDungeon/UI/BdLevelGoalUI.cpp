// Fill out your copyright notice in the Description page of Project Settings.


#include "BdLevelGoalUI.h"

#include "BulletDungeon/BdGameStateBase.h"
#include "BulletDungeon/BulletDungeonGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UBdLevelGoalUI::NativeConstruct()
{
	Super::NativeConstruct();
	auto GM = Cast<ABulletDungeonGameModeBase>(UGameplayStatics::GetGameMode(this));
	GM->RefreshLevel.AddDynamic(this,&UBdLevelGoalUI::UpdateUI);
	
}

void UBdLevelGoalUI::UpdateUI()
{
	GoalItems.Empty();
	auto GM = Cast<ABulletDungeonGameModeBase>(UGameplayStatics::GetGameMode(this));
	auto GS = GM->GetGameState<ABdGameStateBase>();
	auto UnfinishedGoal = GS->GetUnfinishedGoal();
	for (auto i = UnfinishedGoal.CreateIterator(); i; ++i)
	{
		
	}
}
