// Fill out your copyright notice in the Description page of Project Settings.


#include "BdWeaponBase.h"

#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BulletDungeon/AbilitySystem/Abilities/BdGameplayAbility.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "BulletDungeon/Character/BdCharacterHero.h"
#include "BulletDungeon/Player/BdPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"

ABdWeaponBase::ABdWeaponBase()
{
}

void ABdWeaponBase::Shoot_Implementation()
{
	FVector StartLocation = CastChecked<ABdCharacterHero>(Equiper)->GetCameraLocation();
	FRotator ShootDirection = CastChecked<ABdCharacterHero>(Equiper)->GetControlRotation();
}

void ABdWeaponBase::AddWeaponAbilities()
{
}

void ABdWeaponBase::RemoveWeaponAbilities()
{
	
}

TSubclassOf<ABdAmmoBase> ABdWeaponBase::GetAmmoClass()
{
	return AmmoClass;
}

void ABdWeaponBase::Equip_Implementation()
{
	//add abilities from spec handle
	UBdAbilitySystemComponent* ASC = Cast<UBdAbilitySystemComponent>(
		Cast<ABdCharacterBase>(Equiper)->GetAbilitySystemComponent());
	if (ASC)
	{
		for (TSubclassOf<UBdGameplayAbility> Ability : Abilities)
		{
			FGameplayAbilitySpecHandle AbilityHandle = ASC->GiveAbility(
				FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
			AbilitySpecHandles.Add(AbilityHandle);
			UKismetSystemLibrary::PrintString(this, Ability->GetName());
		}

		ABdCharacterHero* Hero = Cast<ABdCharacterHero>(Equiper);
		ABdPlayerState* PS = Cast<ABdPlayerState>(Hero->GetPlayerState());
		PS->GetWeaponAttributeSet()->SetReserveAmmo(Ammos);
		PS->GetWeaponAttributeSet()->SetMaxAmmo(MaxAmmos);
		PS->GetWeaponAttributeSet()->SetAmmoDamage(AmmoDamage);
	}
}


void ABdWeaponBase::UnEquip_Implementation()
{
	// remove abilities from spec handle
	UBdAbilitySystemComponent* ASC = Cast<UBdAbilitySystemComponent>(
		Cast<ABdCharacterBase>(Equiper)->GetAbilitySystemComponent());
	if (ASC)
	{
		for (FGameplayAbilitySpecHandle AbilityHandle : AbilitySpecHandles)
		{
			ASC->ClearAbility(AbilityHandle);
		}
		ABdCharacterHero* Hero = Cast<ABdCharacterHero>(Equiper);
		ABdPlayerState* PS = Cast<ABdPlayerState>(Hero->GetPlayerState());
		Ammos = PS->GetWeaponAttributeSet()->GetReserveAmmo();
	}
}

void ABdWeaponBase::EquipFromInventory_Implementation()
{
	SkeletalMeshComponent->SetVisibility(true, true);

	Equip_Implementation();
}

void ABdWeaponBase::UnEquipFromInventory_Implementation()
{
	SkeletalMeshComponent->SetVisibility(false, true);
	UnEquip_Implementation();
}

void ABdWeaponBase::Drop_Implementation()
{
	UnEquip_Implementation();
	SetOwner(nullptr);
	Equiper = nullptr;
}
