// Fill out your copyright notice in the Description page of Project Settings.


#include "BdGEReloadExecutionCalc.h"

#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "BulletDungeon/Character/BdCharacterHero.h"
#include "Kismet/KismetSystemLibrary.h"

struct FBdReloadStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxAmmo);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ReserveAmmo);
	DECLARE_ATTRIBUTE_CAPTUREDEF(InventoryAmmo);

	FBdReloadStatics()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdWeaponAttributeSet, MaxAmmo, Target, true);


		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdWeaponAttributeSet, ReserveAmmo, Target, true);
		// Capture the Target's Health. Don't snapshot.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdWeaponAttributeSet, InventoryAmmo, Target, true);
	}
};

static const FBdReloadStatics& ReloadStatics()
{
	static FBdReloadStatics DStatics;
	return DStatics;
}


UBdGEReloadExecutionCalc::UBdGEReloadExecutionCalc()
{
	RelevantAttributesToCapture.Add(FBdReloadStatics().MaxAmmoDef);
	RelevantAttributesToCapture.Add(FBdReloadStatics().ReserveAmmoDef);
	RelevantAttributesToCapture.Add(FBdReloadStatics().InventoryAmmoDef);
}

void UBdGEReloadExecutionCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                      FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayTagContainer AssetTags;
	Spec.GetAllAssetTags(AssetTags);

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float MaxAmmo = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ReloadStatics().MaxAmmoDef, EvaluationParameters,
	                                                           MaxAmmo);
	MaxAmmo = FMath::Max<float>(MaxAmmo, 0.0f);

	float ReserveAmmo = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ReloadStatics().ReserveAmmoDef, EvaluationParameters,
	                                                           ReserveAmmo);
	ReserveAmmo = FMath::Max<float>(ReserveAmmo, 0.0f);

	float InventoryAmmo = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ReloadStatics().InventoryAmmoDef, EvaluationParameters,
	                                                           InventoryAmmo);
	InventoryAmmo = FMath::Max<float>(InventoryAmmo, 0.0f);

	float Cost = MaxAmmo - ReserveAmmo;
	float res = 0;
	UKismetSystemLibrary::PrintString(this, FString::FromInt(static_cast<int>(MaxAmmo)));
	float NewReserveAmmo, NewInventoryAmmo;
	if (Cost > InventoryAmmo)
	{
		NewReserveAmmo = ReserveAmmo + InventoryAmmo;
		NewInventoryAmmo = 0;
		res = InventoryAmmo;
	}
	else
	{
		NewReserveAmmo = MaxAmmo;
		NewInventoryAmmo = InventoryAmmo - Cost;
		res = Cost;
	}

	// TODO: 去背包中找子弹进行消耗
	auto PlayerPawn = SourceAbilitySystemComponent->GetAvatarActor();
	auto InventoryComponent = Cast<UBdInventoryComponent>(Cast<ABdCharacterHero>(PlayerPawn)->GetInventoryComponent());
	InventoryComponent->ConsumeAmmo(res);
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(ReloadStatics().ReserveAmmoProperty, EGameplayModOp::Override, NewReserveAmmo));
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(ReloadStatics().InventoryAmmoProperty, EGameplayModOp::Override,
		                               NewInventoryAmmo));
}
