// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BdEndUpGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETDUNGEON_API ABdEndUpGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	ABdEndUpGameModeBase();

protected:
	UPROPERTY(EditAnywhere,Category="Outpost")
	TSubclassOf<UUserWidget> EndUpUIClass;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* EndUpUI;

	UFUNCTION()
	void InitializeEndUpUI(APlayerController* NewPlayer);
};
