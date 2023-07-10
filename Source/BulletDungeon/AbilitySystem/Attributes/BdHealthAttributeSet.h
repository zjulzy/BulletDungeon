// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "BdHealthAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class BULLETDUNGEON_API UBdHealthAttributeSet : public UBdAttributeSetBase
{
	GENERATED_BODY()
public:
	UBdHealthAttributeSet();

	// 当前生命值
	UPROPERTY(BlueprintReadOnly, Category = "BulletDungeon|Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBdHealthAttributeSet, Health)

	//最大生命值
	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBdHealthAttributeSet,MaxHealth );

	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
