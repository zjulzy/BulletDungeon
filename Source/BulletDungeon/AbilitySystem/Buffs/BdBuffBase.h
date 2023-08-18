// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "BdBuffBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBuffType:uint8
{
	Instant,
	Conditional
};

UENUM(BlueprintType)
enum class EBuffQuality:uint8
{
	Gold UMETA(DisplayName = "Gold"),
	Silver UMETA(DisplayName = "Silver"),
};

UCLASS(Blueprintable)
	class BULLETDUNGEON_API UBdBuffBase : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int LevelLimit;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EBuffQuality Quality;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EBuffType Type;
	
	
	// 该buff拥有的增益集合
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<TSubclassOf<UGameplayEffect>,int>BuffEffects;

	UFUNCTION(BlueprintCallable)
	virtual void ActivateBuff();

	UFUNCTION(BlueprintCallable)
	virtual void CancelBuff();
	
	
};
