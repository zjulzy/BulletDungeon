// Copyright Epic Games, Inc. All Rights Reserved.


#include "BulletDungeonGameModeBase.h"


ABulletDungeonGameModeBase::ABulletDungeonGameModeBase()
{
	PlayerStateClass = ABdPlayerState::StaticClass();
	PlayerControllerClass = ABdPlayerController::StaticClass();
	GameStateClass = ABdGameStateBase::StaticClass();

	DefaultPawnClass = ABdCharacterHero::StaticClass();
	bUseSeamlessTravel = true;

	CurrentLevelLocation = FVector(0, 0, 0);

	LevelNames = {FName("L_StartLevel"), FName("L_DemoMap"), FName("L_NextMap")};
	bLastLevel = false;
	Difficulty = 1;
}

void ABulletDungeonGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetGameState<ABdGameStateBase>()->OnFinishedLevelGoal.AddDynamic(this, &ABulletDungeonGameModeBase::LevelFinished);
	GetGameState<ABdGameStateBase>()->ResetGoal(LevelNames[0]);
}

FVector ABulletDungeonGameModeBase::GetNextLevelLocation()
{
	return FVector(CurrentLevelLocation.X + 30000, 0, 0);
}

void ABulletDungeonGameModeBase::LoadAndTravelNewLevel_Implementation()
{
}

bool ABulletDungeonGameModeBase::CanSpawnEnemy(TSubclassOf<ABdCharacterAI> EnemyClass)
{
	//根据难度和当前环境中的敌人判断是否还能生成其他敌人
	//根据剩余的levelgoal查询是否能生成该类敌人
	ABdGameStateBase* GS = GetGameState<ABdGameStateBase>();
	bool bIsConformDifficulty = GS->GetCurrentWeights() + EnemyClass.GetDefaultObject()->GetWeight() <= Difficulty;
	bool bISConformLevel = true;
	TMap<TSubclassOf<ABdCharacterAI>, int> Enemies;
	TMap<TSubclassOf<UObject>, int> Goals;
	GS->GetCurrentEnemies(Enemies);
	GS->GetUnfinishedGoal(Goals);

	if (Enemies.Find(EnemyClass))
	{
		int Current = Enemies[EnemyClass];
		int Reserve = Goals[EnemyClass];
		bISConformLevel = Current < Reserve;
	}
	else
	{
		bISConformLevel = true;
	}
	return bISConformLevel && bIsConformDifficulty;
}

int ABulletDungeonGameModeBase::GetDifficulty()
{
	return Difficulty;
}

void ABulletDungeonGameModeBase::LevelFinished()
{
	// 在关卡通过后的操作，如果是关底需要通往胜利界面
	if(bLastLevel)
	{
		// 跳转到结算界面
	}else
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParameters.Instigator = nullptr;
		FRotator SpawnRotator = FRotator(0, 0, 0);

		GetWorld()->SpawnActor(TransportClass, &CurrentLevelLocation, &SpawnRotator, SpawnParameters);

		// 为玩家生成buff选择界面
		ABdPlayerController* PC = Cast<ABdPlayerController>(GetWorld()->GetFirstPlayerController());
		UUserWidget* BuffSelectUI = CreateWidget<UUserWidget>(PC, BuffSelectUIClass);
		BuffSelectUI->AddToViewport(1);
	}
	
}


// buff选择界面调用，根据当前通过关卡难度，返回若干个buff
void ABulletDungeonGameModeBase::GetPassBuff(TArray<UBdBuffBase*>& CurrentBuffs, int Count)
{
	srand((unsigned)time(NULL));
	//TODO: 根据目前难度等级返回buff
	for (int i = 0; i < Count; i++)
	{
		auto BuffClass = BuffClasses[rand() % (BuffClasses.Num())];
		CurrentBuffs.Add(NewObject<UBdBuffBase>(this,BuffClass));
	}
}

void ABulletDungeonGameModeBase::TestTravel(uint8 LevelIndex)
{
	// TODO:切换到指定关卡
}
