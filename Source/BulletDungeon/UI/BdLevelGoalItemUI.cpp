// Fill out your copyright notice in the Description page of Project Settings.


#include "BdLevelGoalItemUI.h"


void UBdLevelGoalItemUI::SetGoal(TSubclassOf<UObject> GoalType, int FinishedNum, int TotalNum)
{
	//依据传入的levelgoal格式化item ui中的内容
	GoalTextBlock->SetText(FText::Format(FText::FromString("{0}:{1}"),
	                                     IBdGoalDisplayInterface::Execute_GetDisplayName(GoalType.GetDefaultObject()),
	                                     (FinishedNum)));
	GoalClass = GoalType;
	Remain = FinishedNum;
}
