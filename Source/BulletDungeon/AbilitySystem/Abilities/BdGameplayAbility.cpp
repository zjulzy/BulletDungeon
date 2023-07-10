// Fill out your copyright notice in the Description page of Project Settings.


#include "BdGameplayAbility.h"

UBdGameplayAbility::UBdGameplayAbility()
{
}

void UBdGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
