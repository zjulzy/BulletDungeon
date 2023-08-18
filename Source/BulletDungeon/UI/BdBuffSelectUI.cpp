// Fill out your copyright notice in the Description page of Project Settings.


#include "BdBuffSelectUI.h"

#include "BulletDungeon/BulletDungeonGameModeBase.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UBdBuffSelectUI::GetCandidates()
{
	auto GM = Cast<ABulletDungeonGameModeBase>(UGameplayStatics::GetGameMode(this));
	Candidates.Empty();
	GM->GetPassBuff(Candidates, 3);

	//为每个候选panel设置buff描述
	Cast<UTextBlock>(FirstPanel->GetChildAt(0))->SetText(Candidates[0]->Description);
	Cast<UTextBlock>(SecondPanel->GetChildAt(0))->SetText(Candidates[1]->Description);
	Cast<UTextBlock>(ThirdPanel->GetChildAt(0))->SetText(Candidates[2]->Description);
}

void UBdBuffSelectUI::BuffSelected()
{
}

void UBdBuffSelectUI::Activate()
{
	UGameplayStatics::SetGamePaused(this,true);
	GetCandidates();
	SelectedID = -1;
}

void UBdBuffSelectUI::BuffConfirmed()
{
	if(SelectedID>=0)
	{
		UGameplayStatics::SetGamePaused(this,false);
		Candidates[SelectedID]->ActivateBuff();
		this->RemoveFromParent();
		this->Destruct();
	}
	
	
}
