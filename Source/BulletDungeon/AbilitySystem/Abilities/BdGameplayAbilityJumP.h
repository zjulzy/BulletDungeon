// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BdGameplayAbility.h"
#include "BdGameplayAbilityJumP.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API UBdGameplayAbilityJumP : public UBdGameplayAbility
{
	GENERATED_BODY()

public:
	UBdGameplayAbilityJumP();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
};
