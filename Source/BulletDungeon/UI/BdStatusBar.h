// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BdStatusBar.generated.h"

/**
 * 显示敌人血条等状态
 */
UCLASS()
class BULLETDUNGEON_API UBdStatusBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	class ABdCharacterBase* OwningCharacter;

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	float SetHealth(float NewValue);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	float SetHealthMax(float NewValue);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void SetUpListen();
protected:
	UPROPERTY(BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	float HealthMax;
	
};
