// Fill out your copyright notice in the Description page of Project Settings.


#include "BdLevelGoalUI.h"


void UBdLevelGoalUI::NativeConstruct()
{
	Super::NativeConstruct();

	//绑定gamemode和gamestate中关于关卡刷新和关卡目标更新的委托
	auto GM = Cast<ABulletDungeonGameModeBase>(UGameplayStatics::GetGameMode(this));
	GM->RefreshLevel.AddDynamic(this, &UBdLevelGoalUI::UpdateUI);
	auto GS = GM->GetGameState<ABdGameStateBase>();
	GS->OnFinishGoal.AddDynamic(this, &UBdLevelGoalUI::UpdateGoal);
	UpdateUI();
}

void UBdLevelGoalUI::UpdateUI()
{
	for (auto item : GoalItems)
	{
		item->RemoveFromParent();
	}
	GoalItems.Empty();
	auto GM = Cast<ABulletDungeonGameModeBase>(UGameplayStatics::GetGameMode(this));
	auto GS = GM->GetGameState<ABdGameStateBase>();

	TMap<TSubclassOf<UObject>, int> Goals;
	GS->GetUnfinishedGoal(Goals);
	for (auto i = Goals.CreateIterator(); i; ++i)
	{
		auto GoalItem = Cast<UBdLevelGoalItemUI>(CreateWidget(this->GoalPanel, GoalItemClass));
		GoalItem->SetGoal(i.Key(), i.Value(), 0);
		GoalPanel->AddChildToVerticalBox(GoalItem);
		GoalPanel->AddChild(GoalItem);
		GoalItems.Add(GoalItem);
	}
}

void UBdLevelGoalUI::UpdateGoal(TSubclassOf<UObject> GoalType, int Num)
{
	for (auto item : GoalItems)
	{
		auto i = Cast<UBdLevelGoalItemUI>(item);
		if (i->GoalClass == GoalType)
		{
			i->SetGoal(GoalType, i->Remain - Num, 0);
		}
	}
}
