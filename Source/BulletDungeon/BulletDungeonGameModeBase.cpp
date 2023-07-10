// Copyright Epic Games, Inc. All Rights Reserved.


#include "BulletDungeonGameModeBase.h"

#include "BdGameStateBase.h"
#include "Character/BdCharacterHero.h"
#include "Character/AI/BdCharacterAI.h"
#include "Environment/BdTransport.h"
#include "Player/BdPlayerController.h"
#include "Player/BdPlayerState.h"

ABulletDungeonGameModeBase::ABulletDungeonGameModeBase()
{
	PlayerStateClass = ABdPlayerState::StaticClass();
	PlayerControllerClass = ABdPlayerController::StaticClass();
	GameStateClass = ABdGameStateBase::StaticClass();

	DefaultPawnClass= ABdCharacterHero::StaticClass();
	bUseSeamlessTravel = true;

	CurrentLevelLocation = FVector(0,0,0);

	LevelNames = {FName("L_DemoMap"),FName("L_NextMap")};
}

void ABulletDungeonGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetGameState<ABdGameStateBase>()->OnFinishedLevelGoal.AddDynamic(this,&ABulletDungeonGameModeBase::LevelFinished);
	GetGameState<ABdGameStateBase>()->ResetGoal(LevelNames[0]);
}

FVector ABulletDungeonGameModeBase::GetNextLevelLocation()
{
	return FVector(30000,0,0);
}

void ABulletDungeonGameModeBase::LoadAndTravelNewLevel_Implementation()
{
}

bool ABulletDungeonGameModeBase::CanSpawnEnemy(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	//根据难度和当前环境中的敌人判断是否还能生成其他敌人
	//根据剩余的levelgoal查询是否能生成该类敌人
	ABdGameStateBase* GS = GetGameState<ABdGameStateBase>();
	bool bIsConformDifficulty = GS->GetCurrentWeights()+EnemyClass.GetDefaultObject()->GetWeight()<=Difficulty;
	bool bISConformLevel = true;
	if(GetGameState<ABdGameStateBase>()->GetCurrentEnemies().Find(EnemyClass))
	{
		bISConformLevel = GetGameState<ABdGameStateBase>()->GetCurrentEnemies()[EnemyClass]<GetGameState<ABdGameStateBase>()->GetUnfinishedGoal()[EnemyClass];
	}else
	{
		bISConformLevel = true;
	}
	return bISConformLevel&&bIsConformDifficulty;
}

int ABulletDungeonGameModeBase::GetDifficulty()
{
	return Difficulty;
}

void ABulletDungeonGameModeBase::LevelFinished()
{
	//TODO:在关卡通过后的操作
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParameters.Instigator = nullptr;
	FRotator SpawnRotator = FRotator(0,0,0);
	
	GetWorld()->SpawnActor(TransportClass,&CurrentLevelLocation,&SpawnRotator,SpawnParameters);
}