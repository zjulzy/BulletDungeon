// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BdCharacterBase.h"
#include "InputMappingContext.h"
#include "BulletDungeon/AbilitySystem/Abilities/BdGameplayAbility.h"
#include "BdInteractionComponent.h"
#include "BdInventoryComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BulletDungeon/AbilitySystem/Abilities/BdGameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "BulletDungeon/AbilitySystem/BdAbilitySystemComponent.h"
#include "BulletDungeon/Equipments/Ammo/BdAmmoBase.h"
#include "BulletDungeon/Equipments/Weapon/BdWeaponBase.h"
#include "BulletDungeon/Player/BdPlayerController.h"
#include "BulletDungeon/Player/BdPlayerState.h"
#include "BulletDungeon/UI/BdInventoryUI.h"
#include "BulletDungeon/UI/BdMenuUI.h"
#include "BulletDungeon/UI/BdWeaponSwitchUI.h"
#include "BulletDungeon/UI/HUD/BdInteractionHudUI.h"
#include "Camera/CameraComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BdCharacterHero.generated.h"

/**
 * 玩家所使用的主要character
 */

// 保存玩家持枪状态的枚举
UENUM(BlueprintType)
enum class EWeaponState:uint8
{
	No_Weapon,
	Primary_Weapon
};

UCLASS()
class BULLETDUNGEON_API ABdCharacterHero : public ABdCharacterBase
{
	GENERATED_BODY()

public:
	ABdCharacterHero();

	UPROPERTY(BlueprintReadWrite)
	UBdInteractionHudUI* HUD;

	// 委托 --------------------------------------------------------------------------------------------------------------------------
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeShootingState, bool, bIsShooting);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeAimingState, bool, bIsAiming);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeReloadState, bool, bIsReloading);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnChangeWeaponState, EWeaponState, WeaponState, float, Ammos, float,
	                                              AmmoMax, float, AmmoRemain);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadOnly)
	FOnChangeWeaponState OnChangeWeaponState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadOnly)
	FOnChangeAimingState OnChangeAimingState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadOnly)
	FOnChangeShootingState OnChangeShootingState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadOnly)
	FOnChangeReloadState OnChangeReloadState;

	// 处理input 相关函数 -----------------------------------------------------------------------------------------------------------
#pragma region 	input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Input_Move(const FInputActionValue& InputValue);

	UFUNCTION()
	void input_Lookup(const FInputActionValue& InputValue);

	UFUNCTION()
	void input_Interaction(const FInputActionValue& InputValue);

	UFUNCTION()
	void Input_Aim(const FInputActionValue& InputValue);


	UFUNCTION()
	void Input_UnAim(const FInputActionValue& InputValue);

	UFUNCTION()
	void Input_SwitchWeapon(const FInputActionValue& InputValue);

	UFUNCTION()
	void Input_WeaponList(const FInputActionValue& InputValue);

	UFUNCTION()
	void Input_WeaponListReleased(const FInputActionValue& InputValue);

	UFUNCTION()
	void Input_Inventory(const FInputActionValue& InputValue);

	UFUNCTION(BlueprintCallable)
	void Input_Menu(const FInputActionValue& InputValue);
#pragma endregion
	// -----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
	FVector GetCameraLocation();

	UFUNCTION()
	bool Is_Armed();

	UFUNCTION(BlueprintCallable)
	UBdWeaponSwitchUI* GetWeaponUI();

	UFUNCTION(BlueprintCallable)
	UActorComponent* GetInventoryComponent();

	UFUNCTION()
	ABdWeaponBase* GetMainWeapon();

	UFUNCTION(BlueprintCallable)
	TArray<ABdWeaponBase*> GetWeaponList();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() override;

	// --------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	ABdWeaponBase* GetPrimaryWeapon();

	UFUNCTION(BlueprintCallable)
	bool Set_Weapon(ABdEquipment* Weapon);

	UFUNCTION(BlueprintCallable)
	void Set_WeaponState(EWeaponState NewState);

	UFUNCTION(BlueprintCallable)
	EWeaponState Get_WeaponState();

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle TH_Shoot;

	UFUNCTION(Exec, BlueprintCallable)
	void TestAddCritical(float Value);

	UFUNCTION(Exec, BlueprintCallable)
	void TestAddAttack(float Value);

	UFUNCTION(Exec, BlueprintCallable)
	void TestAddHealth(float Value);

	UFUNCTION(Exec, BlueprintCallable)
	void TestAddMaxHealth(float Value);

protected:
	// Ability input handle ----------------------------------------------------------------------------------------------------
	void TestAbilityInputTriggeredHandle();
	void TestAbilityInputReleasedHandle();
	void JumpAbilityInputTriggeredHandle();
	void JumpAbilityInputReleasedHandle();
	void AttackAbilityInputTriggeredHandle();
	void AttackAbilityInputReleasedHandle();
	void ReloadAbilityInputTriggeredHandle();
	void ReloadAbilityInputReleasedHandle();

	void SendLocalInputToASC(bool bIsPressed, EAbilityInputID InputID);

	// Components --------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBdInteractionComponent* InteractionComponent;

	UPROPERTY(BlueprintReadOnly)
	UBdInventoryComponent* InventoryComponent;


	// input 相关property ---------------------------------------------------------------------------------------------------------------

#pragma region
	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	class UInputAction* IA_Lookup;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	class UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	class UInputAction* IA_Interact;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	class UInputAction* IA_Aim;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	UInputAction* IA_Weapons;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	UInputAction* IA_SwitchWeapon;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	UInputAction* IA_Inventory;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	UInputAction* IA_AbilityTest;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	UInputAction* IA_Reload;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|输入")
	UInputAction* IA_Menu;
#pragma endregion
	// Ability 相关 property--------------------------------------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletDungeon|Ability")
	TArray<TSubclassOf<UBdGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BulletDungeon|Ability")
	TSubclassOf<UBdGameplayAbility> TestStartupAbility;

	// Weapon 相关 property---------------------------------------------------------------------------------------------------------------------------


	UPROPERTY(BlueprintReadWrite)
	ABdWeaponBase* MainWeapon;

	UPROPERTY(EditAnywhere)
	EWeaponState WeaponState;

	UPROPERTY()
	bool bIsAiming;

	UPROPERTY()
	float Ammos;

	UPROPERTY()
	float AmmoMax;

	UPROPERTY()
	float AmmoRemain;


	// UI以及背包相关---------------------------------------------------------------------------------------------------
	// 几个bool值，记录武器切换，背包界面和buff选择界面是否激活
	// 这几个UI界面是互斥的
	bool bActivateInventory;
	bool bActivateWeaponSwitch;
	bool bActivateBuffSelect;
	bool bActivateMenu;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BulletDungeon|UI")
	TSubclassOf<UBdInventoryUI> InventoryUIClass;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|UI")
	TSubclassOf<UBdWeaponSwitchUI> WeaponSwitchUIClass;

	UPROPERTY(EditAnywhere, Category="BulletDungeon|UI")
	TSubclassOf<UBdMenuUI> MenuUIClass;

	UPROPERTY(BlueprintReadOnly)
	UBdWeaponSwitchUI* WeaponSwitchUI;

	UPROPERTY(BlueprintReadOnly)
	UBdInventoryUI* InventoryUI;

	UPROPERTY(BlueprintReadOnly)
	UBdMenuUI* MenuUI;

	UFUNCTION(BlueprintCallable)
	void InitializeWeaponUI();

	UFUNCTION(BlueprintCallable)
	void InitializeInventoryUI();

	UFUNCTION(BlueprintCallable)
	void InitializeMenuUI();

	UFUNCTION(BlueprintCallable)
	void InitializeUI();

public:
	virtual void BeginPlay() override;
};
