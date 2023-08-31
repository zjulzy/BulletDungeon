// Fill out your copyright notice in the Description page of Project Settings.


#include "BdHealer.h"


ABdHealer::ABdHealer()
{
	Type = EEquipmentEnum::Heal;
}

void ABdHealer::Use_Implementation()
{
	Super::Use_Implementation();
}
