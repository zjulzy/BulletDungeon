// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "BdWeaponAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdWeaponAttributeSet : public UBdAttributeSetBase
{
	GENERATED_BODY()
public:
	UBdWeaponAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData ReserveAmmo;
	ATTRIBUTE_ACCESSORS(UBdWeaponAttributeSet, ReserveAmmo)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UBdWeaponAttributeSet, MaxAmmo)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData AmmoDamage;
	ATTRIBUTE_ACCESSORS(UBdWeaponAttributeSet, AmmoDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData InventoryAmmo;
	ATTRIBUTE_ACCESSORS(UBdWeaponAttributeSet, InventoryAmmo)
	
};
