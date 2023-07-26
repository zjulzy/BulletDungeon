// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BulletDungeon/System/Tasks/BdGoalDisplayInterface.h"
#include "BdLevelGoalItemUI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdLevelGoalItemUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSubclassOf<UObject>GoalClass;

	UPROPERTY()
	int Remain;
	
	void SetGoal(TSubclassOf<UObject>GoalType, int FinishedNum, int TotalNum);

protected:
	// static const TMap<TSubclassOf<UObject>, FText> ConvertMap;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* GoalTextBlock;
};
