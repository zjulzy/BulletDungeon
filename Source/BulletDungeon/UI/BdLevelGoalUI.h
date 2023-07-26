// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "BdLevelGoalItemUI.h"
#include "BulletDungeon/BdGameStateBase.h"
#include "BulletDungeon/BulletDungeonGameModeBase.h"
#include "Kismet/GameplayStatics.h"
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
	TSubclassOf<UBdLevelGoalItemUI> GoalItemClass;

	void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateUI();

	UPROPERTY()
	TArray<UUserWidget*> GoalItems;

	UPROPERTY(VisibleAnywhere,meta=(BindWidget))
	UVerticalBox* GoalPanel;

	UFUNCTION(BlueprintCallable)
	void UpdateGoal(TSubclassOf<UObject> GoalType,int Num);
};
