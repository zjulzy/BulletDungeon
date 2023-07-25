// Fill out your copyright notice in the Description page of Project Settings.


#include "BdLevelGoalItemUI.h"

void UBdLevelGoalItemUI::SetGoal(FString& GoalString, int FinishedNum, int TotalNum)
{
	//依据传入的levelgoal格式化item ui中的内容
	GoalTextBlock->SetText(FText::Format(FText::FromString("{0}:{1}/{2}"),ConvertMap[GoalString], (FinishedNum), (TotalNum)));
}
