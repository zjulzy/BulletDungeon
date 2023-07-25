// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BdLevelGoalItemUI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdLevelGoalItemUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetGoal(FString& GoalString, int FinishedNum,int TotalNum);

protected:
	static TMap<FString,FText> ConvertMap = {
		{"",FText::FromString("")},
	};
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* GoalTextBlock;
};
