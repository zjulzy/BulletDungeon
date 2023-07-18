// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BdGEReloadExecutionCalc.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdGEReloadExecutionCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UBdGEReloadExecutionCalc();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
