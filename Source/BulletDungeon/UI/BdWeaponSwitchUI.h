// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletDungeon/Equipments/Weapon/BdWeaponBase.h"
#include "BdWeaponSwitchUI.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdWeaponSwitchUI : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	ABdWeaponBase* GetCurrentWeapon();
	
	UFUNCTION(BlueprintCallable)
	ABdWeaponBase* SetCurrentWeapon(ABdWeaponBase* NewWeapon);

	UPROPERTY(BlueprintReadWrite)
	ACharacter* OwningCharacter;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Rotate(int angle);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void SetUpListen();
protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<float> Angles ={30,330,270,210,150,90};
	
	UPROPERTY(BlueprintReadWrite)
	TArray<ABdWeaponBase*> InventoryWeapons;
	

	UFUNCTION(BlueprintCallable)
	bool  IsAngleLegal(int Target);
	
	UPROPERTY(BlueprintReadWrite)
	int CurrentWeaponID;
	
	int WeaponCapacity;

	FString WeaponInfo;
	float Ammos;
	float MaxAmmos;
	
};
