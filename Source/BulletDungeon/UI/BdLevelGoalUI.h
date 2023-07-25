// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BdLevelGoalUI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdLevelGoalUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBdLevelGoalUI> GoalItemClass;

	void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateUI();

	UPROPERTY()
	TArray<TSubclassOf<UBdLevelGoalUI>> GoalItems;
};
