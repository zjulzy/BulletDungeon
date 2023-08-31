// Fill out your copyright notice in the Description page of Project Settings.


#include "BdInteractionComponent.h"

#include "BulletDungeon/Equipments/BdInteractionInterface.h"

// Sets default values for this component's properties
UBdInteractionComponent::UBdInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBdInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UBdInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	APawn* Pawn = Cast<APawn>(this->GetOwner());
	APlayerController* Controller = Cast<APlayerController>(Pawn->GetController());
	FVector EyeLocation;
	FRotator EyeRotation;
	// Pawn->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	//使用玩家视角进行射线检测
	EyeLocation = Controller->PlayerCameraManager->GetCameraLocation();
	EyeRotation = Controller->GetControlRotation();
	
	FVector Destination = EyeLocation + 1000 * EyeRotation.Vector();
	// DrawDebugLine(GetWorld(),EyeLocation,Destination,FColor::Red,false,2.0f);
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, Destination,
	                                                      CollisionObjectQueryParams);

	if (bIsHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor->Implements<UBdInteractionInterface>())
		{
			if (IBdInteractionInterface::Execute_CanBeInteracted(HitActor))
			{
				if (!CurrentActor)
				{
					// GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,FString("捕获"));
					IsInteractable = true;
					OnInteractionChange.Broadcast(CurrentActor, IsInteractable);
				}
				CurrentActor = HitActor;
			}
		}
		else
		{
			CurrentActor = nullptr;
			IsInteractable = false;
			OnInteractionChange.Broadcast(CurrentActor, IsInteractable);
		}
	}
	else
	{
		CurrentActor = nullptr;
		IsInteractable = false;
		OnInteractionChange.Broadcast(CurrentActor, IsInteractable);
	}
	// ...
}

void UBdInteractionComponent::Interact()
{
	if (CurrentActor)
	{
		IBdInteractionInterface::Execute_Interacted(CurrentActor, Cast<APawn>(GetOwner()));
	}
}
