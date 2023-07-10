// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BdStartUpGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API ABdStartUpGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void PostLogin(APlayerController* NewPlayer) override;

	ABdStartUpGameModeBase();

protected:
	UPROPERTY(EditAnywhere,Category="Outpost")
	TSubclassOf<UUserWidget> StartUpUIClass;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* StartUpUI;

	UFUNCTION()
	void InitializeStartUpUI(APlayerController* NewPlayer);
};
