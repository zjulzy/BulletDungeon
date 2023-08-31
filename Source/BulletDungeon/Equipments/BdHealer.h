// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdEquipment.h"
#include "GameplayEffect.h"
#include "BdHealer.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API ABdHealer : public ABdEquipment
{
	GENERATED_BODY()

public:
	ABdHealer();

	virtual void Use_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayEffect>> UseEffect;
	
};
