// Fill out your copyright notice in the Description page of Project Settings.


#include "BdGameplayAbilityJumP.h"


UBdGameplayAbilityJumP::UBdGameplayAbilityJumP()
{
	AbilityInputID = EAbilityInputID::IA_AbilityJump;
}

void UBdGameplayAbilityJumP::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ACharacter* character = Cast<ACharacter>(GetActorInfo().AvatarActor);
	character->Jump();
	
	this->EndAbility(Handle,ActorInfo,ActivationInfo,true,true);
}
