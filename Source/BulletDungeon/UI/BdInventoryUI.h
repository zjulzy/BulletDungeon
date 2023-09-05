// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "BulletDungeon/Character/BdInventoryComponent.h"
#include "Components/BdInventoryItemUI.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
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
		UE_LOG(LogTemp, Log, TEXT("Selected %d in the inventory"), Index);
		SeletedIndex = Index;
		for (int i = 0; i < Items.Num(); i++)
		{
			if (i != Index)
			{
				Items[i]->Unselected();
			}
		}
		// 显示简介
		if (Index >= 0)
		{
			DescriptionText->SetText(
				InventoryComponent->GetInventoryItems()[Index].ItemClass.GetDefaultObject()->Description);
		}
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetUpListen();

	UFUNCTION(BlueprintCallable)
	void UpdateAttributes(FGameplayAttribute Attribute, float NewValue, float OldValue);

	UPROPERTY(BlueprintReadWrite)
	APawn* OwningCharacter;

	UFUNCTION(BlueprintCallable)
	void UpdateItems(TArray<FInventoryItem>& Items);

	UFUNCTION(BlueprintCallable)
	void Activate();

	UFUNCTION(BlueprintCallable)
	void Deactivate();

	UFUNCTION(BlueprintCallable)
	void UseSelectedItem();

	// 右侧背包中被选中的装备索引
	UPROPERTY(BlueprintReadOnly)
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

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	URichTextBlock* DescriptionText;

	UPROPERTY(BlueprintReadOnly)
	TArray<UBdInventoryItemUI*> Items;

	UPROPERTY(BlueprintReadOnly)
	UBdInventoryComponent* InventoryComponent;
};
