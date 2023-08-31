// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletDungeon/Equipments/Weapon/BdWeaponBase.h"
#include "BdInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

public:
	EEquipmentEnum Type;
	TSubclassOf<ABdEquipment> ItemClass;
	int Num;

	FInventoryItem()
	{
		Type = EEquipmentEnum::Default;
		Num = 0;
	}

	FInventoryItem(TSubclassOf<ABdEquipment> c,int n): ItemClass(c), Num(n)
	{
		Type = ItemClass.GetDefaultObject()->Type;
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLETDUNGEON_API UBdInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeWeaponList, const TArray<ABdWeaponBase*>&, NewList);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateInventoryUI, TArray<FInventoryItem>&, NewList);

#pragma region Weapon
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnChangeWeaponList OnChangeWeaponList;

	// Sets default values for this component's properties
	UBdInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddWeapon(ABdWeaponBase* NewWeapon);

	UFUNCTION(BlueprintCallable)
	bool QueryWeapon(ABdWeaponBase* NewWeapon);

	UFUNCTION(BlueprintCallable)
	TArray<ABdWeaponBase*> GetWeaponList();
#pragma endregion

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnUpdateInventoryUI OnUpdateInventoryUI;

	UFUNCTION(BlueprintCallable)
	void Reorganize();

	UFUNCTION(BlueprintCallable)
	bool AddItem(TSubclassOf<ABdEquipment> ItemClass, int Num);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	TArray<ABdEquipment*> Equipments;

	UPROPERTY(BlueprintReadWrite)
	TArray<ABdWeaponBase*> Weapons;

	UPROPERTY(BlueprintReadWrite)
	TArray<FInventoryItem> InventoryItems;

	int WeaponCapacity;
	int ItemCapacity;
	int StackCapacity;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
