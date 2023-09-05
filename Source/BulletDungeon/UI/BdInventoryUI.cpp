// Fill out your copyright notice in the Description page of Project Settings.


#include "BdInventoryUI.h"

#include "Blueprint/WidgetTree.h"
#include "BulletDungeon/AbilitySystem/BdAsyncTaskAttributeChanged.h"
#include "BulletDungeon/Character/BdCharacterHero.h"
#include "Kismet/GameplayStatics.h"

void UBdInventoryUI::SetUpListen_Implementation()
{
	// TODO: 为任务主界面绑定属性变化监听事件
	ABdCharacterHero* PlayerCharacter = Cast<ABdCharacterHero>(GetOwningPlayerPawn());
	auto ASC = PlayerCharacter->GetAbilitySystemComponent();
	TArray<FGameplayAttribute> Attributes = {
		UBdHealthAttributeSet::GetHealthAttribute(),
		UBdHealthAttributeSet::GetMaxHealthAttribute(),
		UBdCombatAttributeSet::GetAttackMultiAttribute(),
		UBdCombatAttributeSet::GetCriticalRateAttribute(),
		UBdCombatAttributeSet::GetCriticalDamageRateAttribute(),
		UBdCombatAttributeSet::GetDefenceAttribute(),
		UBdCombatAttributeSet::GetPenetrateAttribute(),
		UBdWeaponAttributeSet::GetAmmoDamageAttribute(),
		UBdWeaponAttributeSet::GetShootSpeedAttribute(),
		UBdWeaponAttributeSet::GetReserveAmmoAttribute(),
		UBdWeaponAttributeSet::GetInventoryAmmoAttribute()
	};
	auto Task = UBdAsyncTaskAttributeChanged::ListenForAttributesChange(ASC, Attributes);
	Task->OnAttributeChanged.AddDynamic(this, &UBdInventoryUI::UpdateAttributes);
	auto Owner = Cast<ABdCharacterHero>(OwningCharacter);
	auto IC = Cast<UBdInventoryComponent>(Owner->GetInventoryComponent());
	IC->OnUpdateInventoryUI.AddDynamic(this, &UBdInventoryUI::UpdateItems);
}

void UBdInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();
	// 获取所有子控件
	auto Panel = WidgetTree->FindWidget<UWidget>(TEXT("GridPanel"));
	TArray<UWidget*> ItemWidgets;
	WidgetTree->GetChildWidgets(Panel, ItemWidgets);
	for (int i = 0; i < ItemWidgets.Num(); i++)
	{
		Items.Add(Cast<UBdInventoryItemUI>(ItemWidgets[i]));
		Cast<UBdInventoryItemUI>(ItemWidgets[i])->Index = i;
		Cast<UBdInventoryItemUI>(ItemWidgets[i])->OnSelectItem.AddUObject(this, &UBdInventoryUI::Selected);
	}
	SeletedIndex = -1;
	InventoryComponent = Cast<UBdInventoryComponent>(Cast<ABdCharacterHero>(OwningCharacter)->GetInventoryComponent());
}


void UBdInventoryUI::UpdateAttributes(FGameplayAttribute Attribute, float NewValue, float OldValue)
{
	// 根据UI设计attribute改变时更新UI内容
	if (Attribute == UBdHealthAttributeSet::GetHealthAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Health changed from %f to %f"), OldValue, NewValue);
	}
	else if (Attribute == UBdCombatAttributeSet::GetAttackMultiAttribute())
	{
	}
	else if (Attribute == UBdCombatAttributeSet::GetCriticalRateAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("CriticalRate changed from %f to %f"), OldValue, NewValue);
		CriticalRateText->SetText(FText::FromString(TEXT("暴击率：") + FString::SanitizeFloat(NewValue)));
	}
	else if (Attribute == UBdCombatAttributeSet::GetCriticalDamageRateAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("CriticalDamageRate changed from %f to %f"), OldValue, NewValue);
		CriticalDamageRateText->SetText(FText::FromString(TEXT("暴击伤害：") + FString::SanitizeFloat(NewValue)));
	}
	else if (Attribute == UBdCombatAttributeSet::GetDefenceAttribute())
	{
	}
	else if (Attribute == UBdCombatAttributeSet::GetPenetrateAttribute())
	{
	}
	else if (Attribute == UBdWeaponAttributeSet::GetShootSpeedAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("ShootSpeed changed from %f to %f"), OldValue, NewValue);
		ShootSpeedText->SetText(FText::FromString(TEXT("射速：") + FString::SanitizeFloat(1 / NewValue)));
	}
	else if (Attribute == UBdWeaponAttributeSet::GetReserveAmmoAttribute())
	{
	}
	else if (Attribute == UBdWeaponAttributeSet::GetInventoryAmmoAttribute())
	{
	}
	else if (Attribute == UBdWeaponAttributeSet::GetAmmoDamageAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("AmmoDamage changed from %f to %f"), OldValue, NewValue);
		AttackText->SetText(FText::FromString(TEXT("攻击力：") + FString::SanitizeFloat(NewValue)));
	}
}

void UBdInventoryUI::UpdateItems(TArray<FInventoryItem>& Its)
{
	// 基于传入list更新UI中的背包界面
	for (int i = 0; i < Its.Num(); i++)
	{
		if(Its[i].Num)
		{
			Items[i]->Activate(Its[i].ItemClass, Its[i].Num);
		}else
		{
			Items[i]->Deactivate();
		}
	}
	// 需要取消选中
	Selected(-1);
}

void UBdInventoryUI::Activate()
{
	SetVisibility(ESlateVisibility::Visible);
	// 启用仓库UI需要先将游戏暂停
	// 有两种暂停方式，一种是将时间膨胀设置为0，另一种则是直接将游戏暂停
	// 这里采用前者，防止游戏暂停后不响应玩家的输入事件
	// UGameplayStatics::SetGamePaused(this, true);
	UGameplayStatics::SetGlobalTimeDilation(this,0);

	// 启用鼠标以及相关点击和悬浮事件
	ABdPlayerController* PC = Cast<ABdPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PC->bShowMouseCursor = true;
	PC->bEnableMouseOverEvents = true;
	PC->bEnableClickEvents = true;
}

void UBdInventoryUI::Deactivate()
{
	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGlobalTimeDilation(this,1);
	// 隐藏鼠标
	ABdPlayerController* PC = Cast<ABdPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PC->bShowMouseCursor = false;
	PC->bEnableMouseOverEvents = false;
	PC->bEnableClickEvents = false;
}

void UBdInventoryUI::UseSelectedItem()
{
	if (SeletedIndex != -1)
	{
		InventoryComponent->UseInventoryItem(SeletedIndex, 1);
	}
}
