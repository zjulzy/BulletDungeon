// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "BulletDungeon/Character/BdInventoryComponent.h"
#include "Components/BdInventoryItemUI.h"
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
	UFUNCTION()
	virtual void NativeConstruct() override;

	inline void Selected(int Index)
	{
		SeletedIndex = Index;
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetUpListen();

	UFUNCTION(BlueprintCallable)
	void UpdateAttributes(FGameplayAttribute Attribute, float NewValue, float OldValue);

	UPROPERTY(BlueprintReadWrite)
	APawn* OwningCharacter;

	UFUNCTION(BlueprintCallable)
	void UpdateItems(TArray<FInventoryItem>& Items);

	// 右侧背包中被选中的装备索引
	int SeletedIndex;

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

	UPROPERTY(BlueprintReadOnly)
	TArray<UBdInventoryItemUI*> Items;

	UPROPERTY(BlueprintReadOnly)
	UBdInventoryComponent* InventoryComponent;
};
