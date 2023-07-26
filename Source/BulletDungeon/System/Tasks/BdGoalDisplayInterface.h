// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BdGoalDisplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBdGoalDisplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BULLETDUNGEON_API IBdGoalDisplayInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	FText GetDisplayName();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
