// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAmmoBase.h"

#include "BulletDungeon/Character/BdCharacterHero.h"
#include "BulletDungeon/Equipments/Weapon/BdWeaponBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABdAmmoBase::ABdAmmoBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(5.0f);
	RootComponent = SphereComponent;
	ProjectileEffect = CreateDefaultSubobject<UParticleSystemComponent>("ProjectileEffect");
	ProjectileEffect->SetupAttachment(RootComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	

	// SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AOPAmmo::OnActorOverlap);
	SphereComponent->OnComponentHit.AddDynamic(this,&ABdAmmoBase::OnActorHit);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 50000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void ABdAmmoBase::BeginPlay()
{
	Super::BeginPlay();
	AActor* IS = GetInstigator();
	if(IS)
	{
		SphereComponent->IgnoreActorWhenMoving(IS,true);
		SphereComponent->IgnoreActorWhenMoving(Cast<ABdCharacterHero>(this->GetInstigator())->GetMainWeapon(),true);
	}
	
}

// Called every frame
void ABdAmmoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABdAmmoBase::OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherPrimitiveComponent, int I, bool bArg, const FHitResult& HitResult)
{
	UKismetSystemLibrary::PrintString(this, "ammo overlap with"+OtherActor->GetName());
	// if(OtherActor)
	// {
	// 	if(OtherActor!=this->GetInstigator())
	// 	{
	// 		AOPCharacterHero* Source = Cast<AOPCharacterHero>(GetInstigator());
	// 		UOPAbilitySystemComponent* SourceASC = Cast<UOPAbilitySystemComponent>(Source->GetAbilitySystemComponent());
	// 		if(OtherActor->Implements<UAbilitySystemInterface>())
	// 		{
	// 			UKismetSystemLibrary::PrintString(this, "damage");
	// 			
	// 			SourceASC->ApplyGameplayEffectToTarget(AmmoDamageGE,Cast<AOPCharacterAI>(OtherActor)->GetAbilitySystemComponent(),1,FGameplayEffectContextHandle());
	// 		}
	// 		Destroy();
	// 	}
	// }
}

void ABdAmmoBase::OnActorHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherPrimitiveComponent, FVector Normal, const FHitResult& HitResult)
{
	UKismetSystemLibrary::PrintString(this, "ammo hit");
	Destroy();
}

