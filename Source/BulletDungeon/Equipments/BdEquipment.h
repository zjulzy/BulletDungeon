// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "BdInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "BdEquipment.generated.h"

UENUM(BlueprintType)
enum class EEquipmentEnum:uint8
{
	Default,
	Heal,
	RifleAmmo,
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

	UPROPERTY(EditAnywhere)
	FText Description;

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

	UFUNCTION(BlueprintCallable)
	void InteractionEffectApply(APawn* Target);

	UPROPERTY(BlueprintReadWrite)
	APawn* Equiper;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int BaseNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<UGameplayEffect>, int> InteractionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<UGameplayEffect>, int> UseEffect;

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bCanBeUsed;
	
	UFUNCTION(BlueprintCallable)
	void Interacted_Implementation(APawn* InstigatorPawn) override;

	// 装备在加入到背包之后可以使用产生一定效果
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use(APawn* Target);
	virtual void Use_Implementation(APawn* Target);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
