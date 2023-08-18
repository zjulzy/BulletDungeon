// Fill out your copyright notice in the Description page of Project Settings.


#include "BdInventoryUI.h"

#include "BulletDungeon/AbilitySystem/BdAsyncTaskAttributeChanged.h"
#include "BulletDungeon/Character/BdCharacterHero.h"

void UBdInventoryUI::SetUpListen_Implementation()
{
	// TODO: 为任务主界面绑定属性变化监听事件
	ABdCharacterHero* PlayerCharacter = Cast<ABdCharacterHero>(GetOwningPlayerPawn());
	auto ASC = PlayerCharacter->GetAbilitySystemComponent();
	TArray<FGameplayAttribute> Attributes = {
		UBdHealthAttributeSet::GetHealthAttribute(),
		UBdHealthAttributeSet::GetMaxHealthAttribute(),
		UBdCombatAttributeSet::GetAttackMultiAttribute(),
		UBdCombatAttributeSet::GetCriticalRateAttribute(),
		UBdCombatAttributeSet::GetCriticalDamageRateAttribute(),
		UBdCombatAttributeSet::GetDefenceAttribute(),
		UBdCombatAttributeSet::GetPenetrateAttribute(),
		UBdWeaponAttributeSet::GetAmmoDamageAttribute(),
		UBdWeaponAttributeSet::GetShootSpeedAttribute(),
		UBdWeaponAttributeSet::GetReserveAmmoAttribute(),
		UBdWeaponAttributeSet::GetInventoryAmmoAttribute()
	};
	auto Task = UBdAsyncTaskAttributeChanged::ListenForAttributesChange(ASC, Attributes);
	Task->OnAttributeChanged.AddDynamic(this, &UBdInventoryUI::UpdateAttributes);
}

void UBdInventoryUI::UpdateAttributes(FGameplayAttribute Attribute, float NewValue, float OldValue)
{
	// 根据UI设计attribute改变时更新UI内容
	if (Attribute == UBdHealthAttributeSet::GetHealthAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Health changed from %f to %f"), OldValue, NewValue);
	}
	else if (Attribute == UBdCombatAttributeSet::GetAttackMultiAttribute())
	{

	}
	else if (Attribute == UBdCombatAttributeSet::GetCriticalRateAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("CriticalRate changed from %f to %f"), OldValue, NewValue);
		CriticalRateText->SetText(FText::FromString(TEXT("暴击率：") + FString::SanitizeFloat(NewValue)));
	}
	else if (Attribute == UBdCombatAttributeSet::GetCriticalDamageRateAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("CriticalDamageRate changed from %f to %f"), OldValue, NewValue);
		CriticalDamageRateText->SetText(FText::FromString(TEXT("暴击伤害：") + FString::SanitizeFloat(NewValue)));
	}
	else if (Attribute == UBdCombatAttributeSet::GetDefenceAttribute())
	{

	}
	else if (Attribute == UBdCombatAttributeSet::GetPenetrateAttribute())
	{

	}
	else if (Attribute == UBdWeaponAttributeSet::GetShootSpeedAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("ShootSpeed changed from %f to %f"), OldValue, NewValue);
		ShootSpeedText->SetText(FText::FromString(TEXT("射速：") + FString::SanitizeFloat(NewValue)));
	}
	else if (Attribute == UBdWeaponAttributeSet::GetReserveAmmoAttribute())
	{

	}
	else if (Attribute == UBdWeaponAttributeSet::GetInventoryAmmoAttribute())
	{

	}
	else if (Attribute == UBdWeaponAttributeSet::GetAmmoDamageAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("AmmoDamage changed from %f to %f"), OldValue, NewValue);
		AttackText->SetText(FText::FromString(TEXT("攻击力：") + FString::SanitizeFloat(NewValue)));
	}
}
