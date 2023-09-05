// Fill out your copyright notice in the Description page of Project Settings.


#include "BdCharacterAI.h"

#include "BulletDungeon/BulletDungeonGameModeBase.h"
#include "BulletDungeon/BdGameStateBase.h"
#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdCombatAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdHealthAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "BulletDungeon/Player/BdPlayerController.h"
#include "BulletDungeon/UI/BdStatusBar.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


FText ABdCharacterAI::GetDisplayName_Implementation()
{
	return FText::FromString("empty");
}

ABdCharacterAI::ABdCharacterAI()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBdAbilitySystemComponent>("AbilitySystemComponent");
	HealthAttributes = CreateDefaultSubobject<UBdHealthAttributeSet>("HealthAttributes");
	CombatAttributes = CreateDefaultSubobject<UBdCombatAttributeSet>("CombatAttributes");
	WeaponAttributes = CreateDefaultSubobject<UBdWeaponAttributeSet>("WeaponAttributes");
	

	// 初始化血条
	StatusBarComponent = CreateDefaultSubobject<UWidgetComponent>(FName("UIFloatingStatusBarComponent"));
	StatusBarComponent->SetupAttachment(RootComponent);
	StatusBarComponent->SetRelativeLocation(FVector(0, 0, 100));
	StatusBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	StatusBarComponent->SetDrawSize(FVector2D(100, 100));

	//通过委托通知gamestate和levelgoal
	
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if(GM)
	{
		OnKilledEnemy.AddUObject(Cast<ABulletDungeonGameModeBase>(GM)->GetGameState<ABdGameStateBase>(),&ABdGameStateBase::OnEnemyKilled);
		OnKilledEnemy.AddUObject(Cast<ABulletDungeonGameModeBase>(GM)->GetGameState<ABdGameStateBase>(),&ABdGameStateBase::OnReduceEnemy);
	}
	weight = 0;
}

UAbilitySystemComponent* ABdCharacterAI::GetAbilitySystemComponent()
{
	return AbilitySystemComponent;
}

void ABdCharacterAI::InitializeStatusBar()
{
	if(IsPlayerControlled() && IsLocallyControlled())
	{
		return ;
	}
	if(!IsValid(AbilitySystemComponent) || IsValid(StatusBar))
	{
		return ;
	}
	ABdPlayerController* PC = Cast<ABdPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if(PC && PC->IsLocalPlayerController()){
		if(StatusBarClass)
		{
			StatusBar = CreateWidget<UBdStatusBar>(PC,StatusBarClass);
		
			if(StatusBar)
			{
				UKismetSystemLibrary::PrintString(this,"initialize statusbar");
				StatusBarComponent->SetWidget(StatusBar);

				StatusBar->SetHealth(GetHealth());
				StatusBar->SetHealthMax(GetHealthMax());
				StatusBar->OwningCharacter = this;
				StatusBar->SetUpListen();
				StatusBarComponent->SetVisibility(true,true);
			}
		}
	}
}

void ABdCharacterAI::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	this->AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

float ABdCharacterAI::GetWeight()
{
	return weight;
}


void ABdCharacterAI::BeginPlay()
{
	Super::BeginPlay();
	InitializeStatusBar();
}

void ABdCharacterAI::OnKilled()
{
	OnKilledEnemy.Broadcast(this->GetClass());
	Destroy();
}
