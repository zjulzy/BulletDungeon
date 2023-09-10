// Fill out your copyright notice in the Description page of Project Settings.


#include "BdWeaponBase.h"

#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BulletDungeon/AbilitySystem/Abilities/BdGameplayAbility.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "BulletDungeon/Character/BdCharacterHero.h"
#include "BulletDungeon/Player/BdPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ABdWeaponBase::ABdWeaponBase()
{
}

ABdWeaponBase::~ABdWeaponBase()
{
}

void ABdWeaponBase::Shoot_Implementation()
{
	FVector StartLocation = CastChecked<ABdCharacterHero>(Equiper)->GetCameraLocation();
	FRotator ShootDirection = CastChecked<ABdCharacterHero>(Equiper)->GetControlRotation();
}

void ABdWeaponBase::AddWeaponAbilities()
{
}

void ABdWeaponBase::RemoveWeaponAbilities()
{
}

TSubclassOf<ABdAmmoBase> ABdWeaponBase::GetAmmoClass()
{
	return AmmoClass;
}

void ABdWeaponBase::Equip_Implementation()
{
	//add abilities from spec handle
	UBdAbilitySystemComponent* ASC = Cast<UBdAbilitySystemComponent>(
		Cast<ABdCharacterBase>(Equiper)->GetAbilitySystemComponent());
	if (ASC)
	{
		for (TSubclassOf<UBdGameplayAbility> Ability : Abilities)
		{
			FGameplayAbilitySpecHandle AbilityHandle = ASC->GiveAbility(
				FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
			AbilitySpecHandles.Add(AbilityHandle);
			UKismetSystemLibrary::PrintString(this, Ability->GetName());
		}

		ABdCharacterHero* Hero = Cast<ABdCharacterHero>(Equiper);
		ABdPlayerState* PS = Cast<ABdPlayerState>(Hero->GetPlayerState());
		PS->GetWeaponAttributeSet()->SetReserveAmmo(Ammos);
		PS->GetWeaponAttributeSet()->SetMaxAmmo(MaxAmmos);
		PS->GetWeaponAttributeSet()->SetAmmoDamage(AmmoDamage);
	}
}


void ABdWeaponBase::UnEquip_Implementation()
{
	// remove abilities from spec handle
	UBdAbilitySystemComponent* ASC = Cast<UBdAbilitySystemComponent>(
		Cast<ABdCharacterBase>(Equiper)->GetAbilitySystemComponent());
	if (ASC)
	{
		for (FGameplayAbilitySpecHandle AbilityHandle : AbilitySpecHandles)
		{
			ASC->ClearAbility(AbilityHandle);
		}
		ABdCharacterHero* Hero = Cast<ABdCharacterHero>(Equiper);
		ABdPlayerState* PS = Cast<ABdPlayerState>(Hero->GetPlayerState());
		Ammos = PS->GetWeaponAttributeSet()->GetReserveAmmo();
	}
}

void ABdWeaponBase::EquipFromInventory_Implementation()
{
	SkeletalMeshComponent->SetVisibility(true, true);

	Equip_Implementation();
}

void ABdWeaponBase::UnEquipFromInventory_Implementation()
{
	SkeletalMeshComponent->SetVisibility(false, true);
	UnEquip_Implementation();
}

void ABdWeaponBase::Drop_Implementation()
{
	UnEquip_Implementation();
	SetOwner(nullptr);
	Equiper = nullptr;
}

ABdAmmoBase* ABdWeaponBase::Primary_Attack()
{
	ABdAmmoBase* res = nullptr;
	bIsFiring = true;

	// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black,TEXT("步枪攻击"));
	Shoot();
	// SetActorRotation(FRotator(GetActorRotation().Pitch, GetControlRotation().Yaw, GetActorRotation().Roll));
	
	// 施加后坐力----------------------------------------------------------------------------·
	FVector EyeDir = Equiper->GetControlRotation().Vector();
	if (RecoilInstance)
	{
		EyeDir.Normalize();
		FVector UpDir(0, 0, 1);
		FVector RightDir = FVector::CrossProduct(EyeDir, UpDir);
		RightDir.Normalize();

		float SpreadUp = 0, SpreadRight = 0;
		if (RecoilInstance)
		{
			RecoilInstance->GetDirectionalSpread(CurrentFiredAmmo, SpreadUp, SpreadRight);
		}
		EyeDir += UpDir * SpreadUp + RightDir * SpreadRight;
		EyeDir.Normalize();

		// 随机扩散
		// 根据扩散系数，在圆锥上取随机向量
		float SpreadScale = 0;
		if (RecoilInstance)
		{
			RecoilInstance->GetRandomSpread(CurrentFiredAmmo, SpreadScale);
		}
		EyeDir = UKismetMathLibrary::RandomUnitVectorInConeInRadians(EyeDir, SpreadScale);
	}
	//发射弹丸
	//碰撞检测相关参数---------------------------------------------------------------------
	FCollisionShape CollsionSphere;
	CollsionSphere.SetSphere(20.0f);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	// for (auto Weapon : Cast<ABdCharacterHero>(Equiper)->GetInventoryComponent()->GetWeaponList())
	// {
	// 	QueryParams.AddIgnoredActor(Weapon);
	// }
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(this->Equiper);

	FVector StartLocation = Cast<ABdCharacterHero>(Equiper)->GetCameraLocation();
	FVector EndLocation = StartLocation + EyeDir * 5000;
	//碰撞检测以及spawn--------------------------------------------------------------------
	FHitResult HitResult;
	if (GetWorld()->SweepSingleByObjectType(HitResult, StartLocation, EndLocation, FQuat::Identity,
											ObjectQueryParams, CollsionSphere, QueryParams))
	{
		EndLocation = HitResult.ImpactPoint;
	}
	//spawn相关参数设置--------------------------------------------------------------------
	FVector WeaponLocation = StartLocation;
	FRotator Rotation = FRotationMatrix::MakeFromX(EndLocation - WeaponLocation).Rotator();
	FTransform SpawnTM = FTransform(Rotation, WeaponLocation);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = Equiper;

	res = Cast<ABdAmmoBase>(GetWorld()->SpawnActor<AActor>(GetAmmoClass(), SpawnTM, SpawnParameters));
	UKismetSystemLibrary::PrintString(this, res ? "spawn success" : "spawn fail");
	CurrentFiredAmmo++;
	// 发射弹丸结束
	if (RecoilInstance){
		float RecoilPitch, RecoilYaw;
		RecoilInstance->GetCameraMovement(CurrentFiredAmmo, RecoilPitch, RecoilYaw);
		ApplyCameraOffset(RecoilPitch*10, RecoilYaw*10);
	}

	return res;
}

void ABdWeaponBase::ApplyCameraOffset(float Pitch, float Yaw)
{
	if (!Equiper)
		return;
	APlayerController* controller = Cast<APlayerController>(Equiper->GetController());
	if (controller)
	{
		controller->AddPitchInput(-(Pitch - PitchOffset));
		controller->AddYawInput(-(Yaw - YawOffset));
		PitchOffset = Pitch;
		YawOffset = Yaw;
	}
}

void ABdWeaponBase::EndFire()
{
	PitchOffsetWhenStop = PitchOffset/CurrentFiredAmmo;
	YawOffsetWhenStop = YawOffset/CurrentFiredAmmo;
	bIsFiring = false;
	SecondsSinceStopFire = 0;
	FiredAmmoWhenStop = CurrentFiredAmmo;
	CurrentFiredAmmo = 0;
	PitchOffset = 0;
	YawOffset = 0;
}

void ABdWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bIsFiring)
	{
		if (Equiper)
		{
			SecondsSinceStopFire += DeltaSeconds;
			
		}
		if (Equiper)
		{
			float RestoreRatio = 1;
			if (RecoilInstance)
				RecoilInstance->GetCameraRestoreRatio(SecondsSinceStopFire, RestoreRatio);
			float TargetPicth = PitchOffsetWhenStop * (1 - RestoreRatio);
			float TargetYaw = YawOffsetWhenStop * (1 - RestoreRatio);
			ApplyCameraOffset(TargetPicth, TargetYaw);
		}
	}
}
