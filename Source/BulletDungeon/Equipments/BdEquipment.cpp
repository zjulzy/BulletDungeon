// Fill out your copyright notice in the Description page of Project Settings.


#include "BdEquipment.h"
#include "GameplayEffect.h"
#include "BdInteractionInterface.h"
#include "BulletDungeon/Character/BdCharacterBase.h"

// Sets default values
ABdEquipment::ABdEquipment()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");

	RootComponent = SkeletalMeshComponent;
	StaticMeshComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetupAttachment(RootComponent);
	Type = EEquipmentEnum::Default;
	BaseNum = 1;
}

bool ABdEquipment::CanBeInteracted_Implementation()
{
	IBdInteractionInterface::CanBeInteracted_Implementation();
	if (!Equiper)
	{
		return true;
	}
	return false;
}

void ABdEquipment::SetEquiper(APawn* NewEquiper)
{
	Equiper = NewEquiper;
}

void ABdEquipment::Use_Implementation(APawn* Target)
{
	auto TargetASC = Cast<ABdCharacterBase>(Target)->GetAbilitySystemComponent();
	for (auto Effect : UseEffect)
	{
		FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
		EffectContext.AddSourceObject(Target);
		FGameplayEffectSpecHandle Handle = TargetASC->MakeOutgoingSpec(Effect.Key, Effect.Value, EffectContext);
		TargetASC->ApplyGameplayEffectSpecToSelf(*Handle.Data.Get());
	}
}

void ABdEquipment::Interacted_Implementation(APawn* InstigatorPawn)
{
	IBdInteractionInterface::Interacted_Implementation(InstigatorPawn);
}

// Called when the game starts or when spawned
void ABdEquipment::BeginPlay()
{
	Super::BeginPlay();
}

void ABdEquipment::InteractionEffectApply(APawn* Target)
{
	auto TargetASC = Cast<ABdCharacterBase>(Target)->GetAbilitySystemComponent();
	for (auto Effect : InteractionEffect)
	{
		FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
		
		EffectContext.AddSourceObject(Target);
		FGameplayEffectSpecHandle Handle = TargetASC->MakeOutgoingSpec(Effect.Key, Effect.Value, EffectContext);
		TargetASC->ApplyGameplayEffectSpecToSelf(*Handle.Data.Get());
	}
}

// Called every frame
void ABdEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
