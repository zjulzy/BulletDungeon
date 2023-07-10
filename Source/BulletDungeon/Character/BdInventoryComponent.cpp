// Fill out your copyright notice in the Description page of Project Settings.


#include "BdInventoryComponent.h"

#include "BdCharacterHero.h"


// Sets default values for this component's properties
UBdInventoryComponent::UBdInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	WeaponCapacity = 6;
	// ...
}

bool UBdInventoryComponent::AddWeapon(ABdWeaponBase* NewWeapon)
{
	if(Weapons.Num()>=WeaponCapacity)
	{
		return false;
	}
	Weapons.Add(NewWeapon);
	Cast<ABdCharacterHero>(GetOwner())->Set_Weapon(NewWeapon);
	NewWeapon->SetEquiper(Cast<ABdCharacterHero>(GetOwner()));
	OnChangeWeaponList.Broadcast(Weapons);
	return true;
}

bool UBdInventoryComponent::QueryWeapon(ABdWeaponBase* NewWeapon)
{
	for(int i=0;i<Weapons.Num();i++)
	{
		if(NewWeapon->WeaponType==Weapons[i]->WeaponType)
		{
			return false;
		}
	}
	return true;
}

TArray<ABdWeaponBase*> UBdInventoryComponent::GetWeaponList()
{
	return Weapons;
}


// Called when the game starts
void UBdInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBdInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

