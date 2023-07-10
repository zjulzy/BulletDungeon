// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitiesModule.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdCombatAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdHealthAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "BdPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API ABdPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ABdPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	UBdHealthAttributeSet* GetHealthAttributeSet();
	
	UFUNCTION(BlueprintCallable)
	UBdWeaponAttributeSet* GetWeaponAttributeSet();
	
	UFUNCTION(BlueprintCallable)
	UBdCombatAttributeSet* GetCombatAttributeSet();
private:
	UPROPERTY()
	class UBdAbilitySystemComponent* AbilitySystemComponent;

	// attribute sets
	UPROPERTY()
	UBdHealthAttributeSet* HealthAttributes;

	UPROPERTY()
	UBdCombatAttributeSet* CombatAttributes;

	UPROPERTY()
	UBdWeaponAttributeSet* WeaponAttributes;
	
};
