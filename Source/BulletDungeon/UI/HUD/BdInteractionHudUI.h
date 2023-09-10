// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletDungeon/Character/AI/BdCharacterAI.h"
#include "BdInteractionHudUI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdInteractionHudUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	UWidget* AddNewEnemyDirection(ABdCharacterAI* Enemy);
};
