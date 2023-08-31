// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "BdInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "BdEquipment.generated.h"

UENUM(BlueprintType)
enum class EEquipmentEnum:uint8
{
	Default,
	Heal,
	Ammo,
	Weapon
};

UCLASS()
class BULLETDUNGEON_API ABdEquipment : public AActor, public IBdInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABdEquipment();
	UPROPERTY(BlueprintReadOnly)
	AActor* SpawnPoint;

	UPROPERTY(BlueprintReadWrite)
	EEquipmentEnum Type;

	UFUNCTION(BlueprintCallable)
	virtual bool CanBeInteracted_Implementation() override;


	UFUNCTION()
	void SetEquiper(APawn* NewEquiper);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* Icon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 不同的装备可能采用谷骨骼网格体或者静态网格体或者niagara
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NiagaraComponent;


	UPROPERTY(BlueprintReadWrite)
	APawn* Equiper;

	// 装备在加入到背包之后可以使用产生一定效果
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use();
	virtual void Use_Implementation();

public:
	UFUNCTION(BlueprintCallable)
	void Interacted_Implementation(APawn* InstigatorPawn) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
