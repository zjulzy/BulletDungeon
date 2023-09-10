// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdDirectionPointerUI.h"
#include "Blueprint/UserWidget.h"
#include "BulletDungeon/Character/AI/BdCharacterAI.h"
#include "Components/Border.h"
#include "BdDirectionUI.generated.h"

/**
 * 玩家屏幕上方显示朝向以及敌人方向的hud
 */
UCLASS()
class BULLETDUNGEON_API UBdDirectionUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	UWidget* AddNewDirection(ABdCharacterAI* Enemy);

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UBorder* DirectionBorder;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UBdDirectionPointerUI> DirectionPointerUIClass;
};
