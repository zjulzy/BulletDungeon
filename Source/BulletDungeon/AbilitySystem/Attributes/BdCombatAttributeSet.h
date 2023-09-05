// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "BdCombatAttributeSet.generated.h"

/**
 * 
 */


UCLASS()
class BULLETDUNGEON_API UBdCombatAttributeSet : public UBdAttributeSetBase
{
	GENERATED_BODY()

public:
	UBdCombatAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "BulletDungeon|Combat")
	FGameplayAttributeData AttackMulti;
	ATTRIBUTE_ACCESSORS(UBdCombatAttributeSet, AttackMulti)

	//防御力可以等效降低伤害
	UPROPERTY(BlueprintReadOnly, Category = "BulletDungeon|Combat")
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UBdCombatAttributeSet, Defence)

	//穿甲值,默认为0
	UPROPERTY(BlueprintReadOnly, Category = "BulletDungeon|Combat")
	FGameplayAttributeData Penetrate;
	ATTRIBUTE_ACCESSORS(UBdCombatAttributeSet, Penetrate)

	//暴击率，默认为25%
	UPROPERTY(BlueprintReadOnly, Category = "BulletDungeon|Combat")
	FGameplayAttributeData CriticalRate;
	ATTRIBUTE_ACCESSORS(UBdCombatAttributeSet, CriticalRate)

	//暴击伤害，默认为200%
	UPROPERTY(BlueprintReadOnly, Category = "BulletDungeon|Combat")
	FGameplayAttributeData CriticalDamageRate;
	ATTRIBUTE_ACCESSORS(UBdCombatAttributeSet, CriticalDamageRate)

	// 伤害数值的中间值元属性
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData DamageValueCache;
	ATTRIBUTE_ACCESSORS(UBdCombatAttributeSet, DamageValueCache)
	
};
