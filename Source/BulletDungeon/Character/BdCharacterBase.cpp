// Fill out your copyright notice in the Description page of Project Settings.


#include "BdCharacterBase.h"

#include "BdAnimationComponent.h"
#include "GameplayEffectTypes.h"
#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdHealthAttributeSet.h"

// Sets default values
ABdCharacterBase::ABdCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AnimationComponent = CreateDefaultSubobject<UBdAnimationComponent>("Animation Component");

}

void ABdCharacterBase::InitializeAttributes()
{
	if(AbilitySystemComponent)
	{
		// Can run on Server and Client
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*(NewHandle.Data.Get()));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("初始化attribute"));

		}
	}
}

UAbilitySystemComponent* ABdCharacterBase::GetAbilitySystemComponent()
{
	return nullptr;
}

float ABdCharacterBase::GetHealth()
{
	if(IsValid(AbilitySystemComponent)&&IsValid(HealthAttributes))
	{
		return HealthAttributes->GetHealth();
	}
	return 0;
}

float ABdCharacterBase::GetHealthMax()
{
	if(IsValid(AbilitySystemComponent)&&IsValid(HealthAttributes))
	{
		return HealthAttributes->GetMaxHealth();
	}
	return 0;
}

// Called when the game starts or when spawned
void ABdCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttributes();
}

// Called every frame
void ABdCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABdCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

