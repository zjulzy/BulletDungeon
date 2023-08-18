// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BdInventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetUpListen();

	UFUNCTION(BlueprintCallable)
	void UpdateAttributes(FGameplayAttribute Attribute, float NewValue, float OldValue);

	APawn* OwningCharacter;

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* AttackText;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* AmmoNumText;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* ShootSpeedText;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* CriticalRateText;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* CriticalDamageRateText;
};
