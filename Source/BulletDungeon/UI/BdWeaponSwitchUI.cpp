// Fill out your copyright notice in the Description page of Project Settings.


#include "BdWeaponSwitchUI.h"



ABdWeaponBase* UBdWeaponSwitchUI::GetCurrentWeapon()
{
	if(CurrentWeaponID>=0)
	{
		return InventoryWeapons[CurrentWeaponID];
	}
	return nullptr;
}

ABdWeaponBase* UBdWeaponSwitchUI::SetCurrentWeapon(ABdWeaponBase* NewWeapon)
{
	return InventoryWeapons[CurrentWeaponID];
}

void UBdWeaponSwitchUI::Rotate_Implementation(int angle)
{
}

bool UBdWeaponSwitchUI::IsAngleLegal(int Target)
{
	int a[6] = {30,330,270,210,150,90};
	Target = Target%360;										
	for(int i =0;i<InventoryWeapons.Num();i++)
	{
		if(a[i]==Target)return true;
	}
	return false;
}
