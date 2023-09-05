// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BdAmmoBase.generated.h"

UENUM(BlueprintType)
enum EAmmoType:uint8
{
	Default,
	Rifle,
	Pistal,
	Rocket
};

UCLASS()
class BULLETDUNGEON_API ABdAmmoBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABdAmmoBase();

	float Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="BulletDungeon")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadOnly, Category="BulletDungeon", EditAnywhere)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletDungeon")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletDungeon")
	class UParticleSystemComponent* ProjectileEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletDungeon")
	class UGameplayEffect* AmmoDamageGE;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherPrimitiveComponent, int I, bool bArg, const FHitResult& HitResult);

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	                UPrimitiveComponent* OtherPrimitiveComponent, FVector Normal, const FHitResult& HitResult);
};
