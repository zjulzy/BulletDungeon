// Fill out your copyright notice in the Description page of Project Settings.


#include "BdGEDemageExecutionCalc.h"

#include "BulletDungeon/AbilitySystem/Attributes/BdCombatAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdHealthAttributeSet.h"
#include "BulletDungeon/AbilitySystem/Attributes/BdWeaponAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"


struct FBdDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AmmoDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackMulti);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	FBdDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdWeaponAttributeSet, AmmoDamage, Source, true);

		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBdCombatAttributeSet, AttackMulti, Source, true);
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
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AmmoDamageDef, EvaluationParameters, AmmoDamage);
	AmmoDamage = FMath::Max<float>(AmmoDamage, 0.0f);

	float AttackMulti = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackMultiDef, EvaluationParameters, AttackMulti);
	AttackMulti = FMath::Max<float>(AttackMulti, 0.0f);

	float Health = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, Health);
	Health = FMath::Max<float>(Health, 0.0f);
	
	float HitDamage = AmmoDamage*AttackMulti;
	
	if(HitDamage>0)
	{
		UKismetSystemLibrary::PrintString(this,"cause damage"+FString::SanitizeFloat(HitDamage));
		UKismetSystemLibrary::PrintString(this,"Target health"+FString::SanitizeFloat(Health));
		// Set the Target's damage meta attribute
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, HitDamage*-1));
	}
}
