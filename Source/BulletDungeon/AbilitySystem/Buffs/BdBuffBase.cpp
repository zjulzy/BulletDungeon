// Fill out your copyright notice in the Description page of Project Settings.


#include "BdBuffBase.h"

#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BulletDungeon/Character/BdCharacterBase.h"
#include "Kismet/GameplayStatics.h"

void UBdBuffBase::ActivateBuff()
{
	auto Player = Cast<ABdCharacterBase>(UGameplayStatics::GetPlayerPawn(this,0));
	UBdAbilitySystemComponent* Target = Cast<UBdAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	if(!Target)
	{
		return;
	}
	// 遍历BuffEffects，将每个effect施加到玩家身上
	for (auto Effect : BuffEffects)
	{
		auto Context = Target->MakeEffectContext();
		Context.AddSourceObject(Target);
		FGameplayEffectSpecHandle Handle = Target->MakeOutgoingSpec(Effect.Key,Effect.Value,Context);
		Target->ApplyGameplayEffectSpecToSelf(*Handle.Data.Get());
		
	}
}

void UBdBuffBase::CancelBuff()
{
}
