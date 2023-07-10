// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BdInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETDUNGEON_API UBdInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBdInteractionComponent();
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FonInteractionChange,AActor* ,TargetActor,bool,IsInteractable);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* CurrentActor;

	UPROPERTY()
	bool IsInteractable;

	UPROPERTY(BlueprintAssignable)
	FonInteractionChange OnInteractionChange;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Interact();
};
