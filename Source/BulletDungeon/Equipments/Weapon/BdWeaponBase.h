// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BulletDungeon/Equipments/BdEquipment.h"
#include "BdWeaponBase.generated.h"

/**
 * 
 */

//声明武器类型的枚举，每个类型对应一个单独的武器型号
UENUM(BlueprintType)
enum class EWeaponType:uint8
{
	WeaponDefault,
	WeaponRifle,
	WeaponRifleDemo1,
	WeaponRifleDemo2
};
UCLASS()
class BULLETDUNGEON_API ABdWeaponBase : public ABdEquipment
{
	GENERATED_BODY()
public:

	ABdWeaponBase();
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="射击")
	float ShootSpeed;

	UPROPERTY()
	float AmmoSpeed;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="射击")
	float Ammos;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="射击")
	float MaxAmmos;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="射击")
	float AmmoDamage;
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Shoot();

	
	UFUNCTION()
	void AddWeaponAbilities();

	UFUNCTION()
	void RemoveWeaponAbilities();
	
	TSubclassOf<ABdAmmoBase> GetAmmoClass();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Equip();
	
	virtual void Equip_Implementation();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void UnEquip();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void EquipFromInventory();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void UnEquipFromInventory();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Drop();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Outpost|Weapon")
	EWeaponType WeaponType;
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Outpost|Weapon")
	TSubclassOf<ABdAmmoBase> AmmoClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Outpost|Weapon")
	FGameplayTag WeaponTag;
	
	// 武器给character赋予的能力以及spec，在装备和接触武器时进行add和remove
	// 目前武器包含攻击能力和reload能力
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Outpost|Weapon")
	TArray<TSubclassOf<UBdGameplayAbility>>Abilities;
	
	UPROPERTY(BlueprintReadOnly, Category = "Outpost|Weapon")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// UPROPERTY()
	// ABdGATA_Trace* GATA_Trace; 
};
