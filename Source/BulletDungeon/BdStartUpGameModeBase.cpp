// Fill out your copyright notice in the Description page of Project Settings.


#include "BdStartUpGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ABdStartUpGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	InitializeStartUpUI(NewPlayer);
	NewPlayer->bShowMouseCursor = true;
}

ABdStartUpGameModeBase::ABdStartUpGameModeBase()
{
}

void ABdStartUpGameModeBase::InitializeStartUpUI(APlayerController* NewPlayer)
{
	if (StartUpUIClass)
	{
		UKismetSystemLibrary::PrintString(this, "1");


		StartUpUI = CreateWidget<UUserWidget>(NewPlayer, StartUpUIClass);
		StartUpUI->AddToViewport();
		auto PC = UGameplayStatics::GetPlayerController(this,0);
		PC->bShowMouseCursor = true;
		
	}
}
