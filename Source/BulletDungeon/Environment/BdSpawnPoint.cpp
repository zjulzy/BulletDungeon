// Fill out your copyright notice in the Description page of Project Settings.


#include "BdSpawnPoint.h"

#include "BulletDungeon/BulletDungeonGameModeBase.h"
#include "BulletDungeon/BdGameStateBase.h"
#include "BulletDungeon/Character/AI/BdCharacterAI.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABdSpawnPoint::ABdSpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnInterval = 1;
}

// Called when the game starts or when spawned
void ABdSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnHandler, this, &ABdSpawnPoint::SpawnEnemy, SpawnInterval, true, -1);
	// 在place in editor，且在editor中运行时需要延迟绑定委托
	ABdGameStateBase* GS = Cast<ABdGameStateBase>(UGameplayStatics::GetGameState(this));
	if (GS)
	{
		OnAddEnemyWeights.AddUObject(GS, &ABdGameStateBase::OnAddEnemy);
	}
}

void ABdSpawnPoint::SpawnEnemy()
{
	//周期性检查场景中的怪物总数并生成怪物
	ABulletDungeonGameModeBase* GM = Cast<ABulletDungeonGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GM->CanSpawnEnemy(EnemyClass))
	{
		//需要随机判断生成以免敌人生成过于频繁
		if (FMath::RandRange(1, 10) <= 5)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			SpawnParameters.Instigator = nullptr;
			FRotator SpawnRotator = FRotator(0, 0, 0);
			FVector SpawnLocation = GetActorLocation();

			auto res = GetWorld()->SpawnActor(EnemyClass, &SpawnLocation, &SpawnRotator, SpawnParameters);
			OnAddEnemyWeights.Broadcast(EnemyClass);

			// TODO:这里后面最好还是重构一下
			// spawn敌人之后通知UI的指示器
			auto PlayerPawn = Cast<ABdCharacterHero>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
			PlayerPawn->HUD->AddNewEnemyDirection(Cast<ABdCharacterAI>(res));
		}
	}
}

// Called every frame
void ABdSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
