// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletDungeon/AbilitySystem/Buffs/BdBuffBase.h"
#include "Components/Button.h"
#include "BdBuffSelectUI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdBuffSelectUI : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void GetCandidates();

	UFUNCTION(BlueprintCallable)
	void BuffSelected();

	UFUNCTION(BlueprintCallable)
	void Activate();

	UFUNCTION(BlueprintCallable)
	void BuffConfirmed();
	
	UPROPERTY(BlueprintReadWrite)
	TArray<UBdBuffBase*> Candidates;
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* FirstPanel;

	UPROPERTY(meta=(BindWidget))
	UButton* SecondPanel;

	UPROPERTY(meta=(BindWidget))
	UButton* ThirdPanel;

	UPROPERTY(meta=(BindWidget),BlueprintReadOnly)
	UButton* ConfirmButton;

	UPROPERTY(BlueprintReadWrite)
	int SelectedID;
	
	
};
