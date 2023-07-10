// Fill out your copyright notice in the Description page of Project Settings.


#include "BdPlayerState.h"

#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdCombatAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdHealthAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"

ABdPlayerState::ABdPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBdAbilitySystemComponent>("AbilitySystemComponent");

	HealthAttributes = CreateDefaultSubobject<UBdHealthAttributeSet>("HealthAttributes");
	CombatAttributes = CreateDefaultSubobject<UBdCombatAttributeSet>("CombatAttributes");
	WeaponAttributes = CreateDefaultSubobject<UBdWeaponAttributeSet>("WeaponAttributes");
	
}

UAbilitySystemComponent* ABdPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBdHealthAttributeSet* ABdPlayerState::GetHealthAttributeSet()
{
	return HealthAttributes;
}

UBdWeaponAttributeSet* ABdPlayerState::GetWeaponAttributeSet()
{
	return WeaponAttributes;
}

UBdCombatAttributeSet* ABdPlayerState::GetCombatAttributeSet()
{
	return CombatAttributes;
}
