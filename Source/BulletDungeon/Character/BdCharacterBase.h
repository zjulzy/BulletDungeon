// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BdAnimationComponent.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdHealthAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdCombatAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "GameFramework/Character.h"
#include "BdCharacterBase.generated.h"

UCLASS()
class BULLETDUNGEON_API ABdCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABdCharacterBase();

	UFUNCTION(BlueprintCallable)
	virtual void InitializeAttributes();

	// 与gas相关的public get函数-------------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealth();

	UFUNCTION(BlueprintCallable)
	float GetHealthMax();
	// ------------------------------------------------------------------------------------------------------------------------
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Animation")
	UBdAnimationComponent* AnimationComponent;

	UPROPERTY(EditAnywhere,Category="Outpost|Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	// GAS 相关指针，ASC 和 attributeset都不位于此处 ---------------------------------------------------------------------------------
	UPROPERTY()
	UBdAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	class UBdWeaponAttributeSet* WeaponAttributes;

	UPROPERTY()
	class UBdHealthAttributeSet* HealthAttributes;

	UPROPERTY()
	class UBdCombatAttributeSet* CombatAttributes;
	// --------------------------------------------------------------------------------------------------------------------------
	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
