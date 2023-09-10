// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdShootEffect.h"
#include "GameplayTagContainer.h"
#include "BulletDungeon/AbilitySystem/Abilities/BdGameplayAbility.h"
#include "BulletDungeon/Equipments/Ammo/BdAmmoBase.h"
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
	virtual ~ABdWeaponBase() override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BulletDungeon|Weapon")
	float ShootSpeed;

	UPROPERTY()
	float AmmoSpeed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="射击")
	UMaterial* LiveMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="射击")
	float Ammos;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="射击")
	float MaxAmmos;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="射击")
	float AmmoDamage;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Shoot();


	UFUNCTION()
	void AddWeaponAbilities();

	UFUNCTION()
	void RemoveWeaponAbilities();

	TSubclassOf<ABdAmmoBase> GetAmmoClass();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Equip();

	virtual void Equip_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnEquip();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EquipFromInventory();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnEquipFromInventory();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Drop();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Outpost|Weapon")
	EWeaponType WeaponType;

	UFUNCTION(BlueprintCallable)
	ABdAmmoBase* Primary_Attack();
	
	UFUNCTION(BlueprintCallable)
	void ApplyCameraOffset(float Pitch, float Yaw);

	bool bIsFiring = false;
	UFUNCTION(BlueprintCallable)
	void EndFire();
	virtual void Tick(float DeltaSeconds) override;
protected:
#pragma region recoil

	// 统计之前射出的子弹数，用于调节后坐力，停止开火后逐渐衰减
	float CurrentFiredAmmo = 0;
	// 统计停火后“休息”时间
	float SecondsSinceStopFire = 0;
	// 记录停止开火时的累计射击子弹数
	float FiredAmmoWhenStop = 0;
	// 统计镜头偏移量
	float PitchOffset = 0, YawOffset = 0;
	// 记录停止开火时的镜头偏移
	float PitchOffsetWhenStop = 0, YawOffsetWhenStop = 0;
	UPROPERTY(Instanced, EditDefaultsOnly, Category="BulletDungeon|Weapon")
	UBdShootEffect* RecoilInstance;
	
#pragma endregion
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Outpost|Weapon")
	TSubclassOf<ABdAmmoBase> AmmoClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Outpost|Weapon")
	FGameplayTag WeaponTag;

	// 武器给character赋予的能力以及spec，在装备和接触武器时进行add和remove
	// 目前武器包含攻击能力和reload能力
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Outpost|Weapon")
	TArray<TSubclassOf<UBdGameplayAbility>> Abilities;

	UPROPERTY(BlueprintReadOnly, Category = "Outpost|Weapon")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// UPROPERTY()
	// ABdGATA_Trace* GATA_Trace; 
};
