// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BdInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBdInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BULLETDUNGEON_API IBdInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Interacted(APawn* InstigatorPawn);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool CanBeInteracted();
};
