// Fill out your copyright notice in the Description page of Project Settings.


#include "BdEndUpGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABdEndUpGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	InitializeEndUpUI(NewPlayer);
	NewPlayer->bShowMouseCursor = true;
}

ABdEndUpGameModeBase::ABdEndUpGameModeBase()
{
}

void ABdEndUpGameModeBase::InitializeEndUpUI(APlayerController* NewPlayer)
{
	if (EndUpUIClass)
	{
		EndUpUI = CreateWidget<UUserWidget>(NewPlayer, EndUpUIClass);
		EndUpUI->AddToViewport();
		auto PC = UGameplayStatics::GetPlayerController(this, 0);
		PC->bShowMouseCursor = true;
	}
}
