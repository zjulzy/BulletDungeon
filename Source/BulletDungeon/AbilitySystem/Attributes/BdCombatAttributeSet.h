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

	//穿甲值
	UPROPERTY(BlueprintReadOnly, Category = "BulletDungeon|Combat")
	FGameplayAttributeData Penetrate;
	ATTRIBUTE_ACCESSORS(UBdCombatAttributeSet, Penetrate)
};
