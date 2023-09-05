// Fill out your copyright notice in the Description page of Project Settings.


#include "BdInventoryComponent.h"
#include <algorithm>
#include "BdCharacterHero.h"


// Sets default values for this component's properties
UBdInventoryComponent::UBdInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	WeaponCapacity = 6;
	ItemCapacity = 24;
	StackCapacity = 99;

	// 为每个格子初始化

	// InventoryItems.Init(FInventoryItem(EEquipmentEnum::Default,0), 24);
	// ...
}

bool UBdInventoryComponent::AddWeapon(ABdWeaponBase* NewWeapon)
{
	if (Weapons.Num() >= WeaponCapacity)
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
	for (int i = 0; i < Weapons.Num(); i++)
	{
		if (NewWeapon->WeaponType == Weapons[i]->WeaponType)
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

void UBdInventoryComponent::Reorganize()
{
	// 实现仓库的整理功能,将可以堆叠的物品类别进行缩减
	// 使用双指针法整理其他物品
	// TODO: 这里似乎还有bug
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i].Num == 0)continue;
		for (int j = 0; j < i; j++)
		{
			if (InventoryItems[j].Num == 0)
			{
				InventoryItems[j].Num = InventoryItems[i].Num;
				InventoryItems[i].Num = 0;
				InventoryItems[j].ItemClass = InventoryItems[i].ItemClass;
				break;
			}
			else if (InventoryItems[j].ItemClass == InventoryItems[i].ItemClass)
			{
				// 如果两个物品类别相同则进行堆叠
				if (InventoryItems[j].Num + InventoryItems[i].Num > StackCapacity)
				{
					InventoryItems[i].Num -= StackCapacity - InventoryItems[j].Num;
					InventoryItems[j].Num = StackCapacity;
				}
				else
				{
					InventoryItems[j].Num += InventoryItems[i].Num;
					InventoryItems[i].Num = 0;
					break;
				}
			}
		}
	}

	// 剔除空的仓库栏位
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i].Num == 0)
		{
			InventoryItems.RemoveAtSwap(i);
			i--;
		}
	}
	OnUpdateInventoryUI.Broadcast(InventoryItems);
}

bool UBdInventoryComponent::AddItem(TSubclassOf<ABdEquipment> ItemClass, int Num)
{
	if (InventoryItems.Num() == ItemCapacity)
	{
		for (int i = 0; i < InventoryItems.Num(); i++)
		{
			if (Num <= 0)break;
			if (InventoryItems[i].ItemClass == ItemClass)
			{
				Num -= StackCapacity - InventoryItems[i].Num;
				InventoryItems[i].Num = std::min(StackCapacity, InventoryItems[i].Num + Num);
			}
		}
		return true;
	}
	else
	{
		InventoryItems.Add(FInventoryItem(ItemClass, Num));
	}
	OnUpdateInventoryUI.Broadcast(InventoryItems);
	return true;
}


TArray<FInventoryItem> UBdInventoryComponent::GetInventoryItems()
{
	return InventoryItems;
}

bool UBdInventoryComponent::UseInventoryItem(int Index, int Num)
{
	// 基于传入的索引找到要使用的装备类别并使用
	auto ItemClass = InventoryItems[Index].ItemClass;
	if (!ItemClass.GetDefaultObject()->bCanBeUsed)return false;
	Cast<ABdEquipment>(ItemClass->GetDefaultObject())->Use(Cast<ABdCharacterHero>(GetOwner()));
	InventoryItems[Index].Num -= Num;
	OnUpdateInventoryUI.Broadcast(InventoryItems);
	return true;
}

void UBdInventoryComponent::ConsumeAmmo(int Num)
{
	//遍历背包中的所有子弹并且消耗
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (Num <= 0)break;
		if (InventoryItems[i].ItemClass.GetDefaultObject()->Type == EEquipmentEnum::RifleAmmo)
		{
			int n = std::min(Num, InventoryItems[i].Num);
			InventoryItems[i].Num -= n;
			Num -= n;
		}
	}
	OnUpdateInventoryUI.Broadcast(InventoryItems);
}


// Called when the game starts
void UBdInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UBdInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
