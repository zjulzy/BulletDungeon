// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletDungeon/Equipments/Weapon/BdWeaponBase.h"
#include "BdInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETDUNGEON_API UBdInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeWeaponList,const TArray<ABdWeaponBase*>&,NewList);

	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnChangeWeaponList OnChangeWeaponList;
	
	// Sets default values for this component's properties
	UBdInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddWeapon(ABdWeaponBase* NewWeapon);

	UFUNCTION(BlueprintCallable)
	bool QueryWeapon(ABdWeaponBase* NewWeapon);

	UFUNCTION(BlueprintCallable)
	TArray<ABdWeaponBase*> GetWeaponList();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	TArray<ABdEquipment*> Equipments;

	UPROPERTY(BlueprintReadWrite)
	TArray<ABdWeaponBase*> Weapons;

	int WeaponCapacity;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
