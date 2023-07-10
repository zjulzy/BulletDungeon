// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BdGameplayAbility.generated.h"

/**
 * 
 */
//与ability的输入激活相关联的枚举
UENUM(BlueprintType)
enum class EAbilityInputID
{
	IA_AbilityNone UMETA(DisplayName = "none ability"),
	IA_AbilityTest UMETA(DisplayName = "test ability"),
	IA_AbilityAttack UMETA(DisplayName = "attack ability"),
	IA_AbilityJump UMETA(DisplayName = "jump ability"),
	IA_AbilityReload UMETA(DisplayName = "reload ability")
};

UCLASS()
class BULLETDUNGEON_API UBdGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	
	UBdGameplayAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditAnywhere,Category="Bullet Dungeon|Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::IA_AbilityNone;
};
