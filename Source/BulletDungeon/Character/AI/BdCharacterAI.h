// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletDungeon/Character/BdCharacterBase.h"
#include "BulletDungeon/System/Tasks/BdGoalDisplayInterface.h"
#include "BulletDungeon/UI/BdStatusBar.h"

#include "BdCharacterAI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API ABdCharacterAI : public ABdCharacterBase,public IBdGoalDisplayInterface
{
	GENERATED_BODY()
	
public:

	virtual FText GetDisplayName_Implementation() override;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnKilledEnemy,TSubclassOf<ABdCharacterAI>);
	FOnKilledEnemy OnKilledEnemy;
	
	ABdCharacterAI();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() override;

	// 初始化血条状态栏，在beginplay中调用
	void InitializeStatusBar();
	
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	float GetWeight();
	
protected:
	// UI 相关 property，主要是血条--------------------------------------------------------------------------------------------------
	UPROPERTY()
	class UWidgetComponent* StatusBarComponent;
	
	UPROPERTY(EditAnywhere,Category="Outpost|UI")
	TSubclassOf<UBdStatusBar> StatusBarClass;

	UPROPERTY()
	class UBdStatusBar* StatusBar;

	UPROPERTY(BlueprintReadWrite)
	ABdCharacterBase* AttackTarget;
	// --------------------------------------------------------------------------------------------------------------------------
	
	UPROPERTY()
	float Ammos;

	UPROPERTY()
	float AmmoMax;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Outpost|Enemy")
	float weight;

	// ASC和attributset指针，ASC位于在AI character中 ----------------------------------------------------------------------------------
	// UPROPERTY()
	// UOPAbilitySystemComponent* AbilitySystemComponent;
	
	// ----------------------------------------------------------------------------------------------------------------------------

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnKilled();
};
