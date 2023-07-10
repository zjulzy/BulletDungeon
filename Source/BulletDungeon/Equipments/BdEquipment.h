// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "BdEquipment.generated.h"

UCLASS()
class BULLETDUNGEON_API ABdEquipment : public AActor,public IBdInteractionInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABdEquipment();

	UFUNCTION(BlueprintCallable)
	virtual bool CanBeInteracted_Implementation() override;

	UFUNCTION()
	void SetEquiper(APawn* NewEquiper);
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UMaterial* Icon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadWrite)
	APawn* Equiper;

	

public:
	UFUNCTION(BlueprintCallable)
	void Interacted_Implementation(APawn* InstigatorPawn) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
