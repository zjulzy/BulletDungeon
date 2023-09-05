// Fill out your copyright notice in the Description page of Project Settings.


#include "BdGEDemageExecutionCalc.h"

#include <random>
#include "BulletDungeon/AbilitySystem/Attributes/BdCombatAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdHealthAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"


struct FBdDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AmmoDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackMulti);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamageRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageValueCache);

	FBdDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdWeaponAttributeSet, AmmoDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdCombatAttributeSet, AttackMulti, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdCombatAttributeSet, CriticalRate, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdCombatAttributeSet, CriticalDamageRate, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdCombatAttributeSet, DamageValueCache, Source, false);
		// Capture the Target's Health. Don't snapshot.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdHealthAttributeSet, Health, Target, false);
	}
};

static const FBdDamageStatics& DamageStatics()
{
	static FBdDamageStatics DStatics;
	return DStatics;
}

UBdGEDemageExecutionCalc::UBdGEDemageExecutionCalc()
{
	RelevantAttributesToCapture.Add(DamageStatics().AmmoDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().AttackMultiDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageValueCacheDef);
}

void UBdGEDemageExecutionCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
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

	float AmmoDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AmmoDamageDef, EvaluationParameters,
	                                                           AmmoDamage);
	AmmoDamage = FMath::Max<float>(AmmoDamage, 0.0f);

	float AttackMulti = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackMultiDef, EvaluationParameters,
	                                                           AttackMulti);
	AttackMulti = FMath::Max<float>(AttackMulti, 0.0f);

	float Health = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, Health);
	Health = FMath::Max<float>(Health, 0.0f);

	float CriticalRate = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalRateDef, EvaluationParameters,
	                                                           CriticalRate);

	float CriticalDamageRate = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalDamageRateDef,
	                                                           EvaluationParameters, CriticalDamageRate);


	// 基于子弹伤害，暴击率，暴击伤害和额外伤害率计算总体伤害
	// 伤害 = 子弹伤害 * (1 + 暴击伤害) * (1 + 额外伤害率)
	std::uniform_real_distribution<double> u(0, 1);
	std::default_random_engine e(time(NULL));
	double Random = u(e);
	float HitDamage = AmmoDamage * (1 + AttackMulti);
	if (Random < CriticalRate)
	{
		HitDamage *= (1 + CriticalDamageRate);
	}

	if (HitDamage > 0)
	{
		UKismetSystemLibrary::PrintString(this, "cause damage" + FString::SanitizeFloat(HitDamage));
		UKismetSystemLibrary::PrintString(this, "Target health" + FString::SanitizeFloat(Health));
		// Set the Target's damage meta attribute
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, HitDamage * -1));
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(DamageStatics().DamageValueCacheProperty, EGameplayModOp::Override,
			                               HitDamage));
	}
}
