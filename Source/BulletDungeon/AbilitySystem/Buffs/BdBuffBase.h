// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BdBuffBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdBuffBase : public UObject
{
	GENERATED_BODY()
public:
	FText Description;

	// 该buff拥有的增益集合
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>>BuffEffects;
	
	
};
