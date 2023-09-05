// Fill out your copyright notice in the Description page of Project Settings.


#include "BdCharacterHero.h"

#include "Kismet/GameplayStatics.h"


ABdCharacterHero::ABdCharacterHero()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InventoryComponent = CreateDefaultSubobject<UBdInventoryComponent>("InventoryComponent");
	InteractionComponent = CreateDefaultSubobject<UBdInteractionComponent>("InteractionComponent");
	bActivateWeaponSwitch = false;
	bActivateInventory = false;
	bActivateBuffSelect = false;
}

void ABdCharacterHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//bind input binding context
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	ULocalPlayer* Player = PlayerController ? PlayerController->GetLocalPlayer() : nullptr;

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("绑定映射开始"));
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputContext)
			{
				InputSystem->AddMappingContext(InputContext, 100);
				// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("绑定映射结束"));
			}
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//基础input绑定
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABdCharacterHero::Input_Move);
		EnhancedInputComponent->BindAction(IA_Lookup, ETriggerEvent::Triggered, this, &ABdCharacterHero::input_Lookup);

		//与ability相关的input绑定
		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this,
		                                   &ABdCharacterHero::AttackAbilityInputTriggeredHandle);
		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Completed, this,
		                                   &ABdCharacterHero::AttackAbilityInputReleasedHandle);
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Started, this,
		                                   &ABdCharacterHero::ReloadAbilityInputTriggeredHandle);
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Completed, this,
		                                   &ABdCharacterHero::ReloadAbilityInputReleasedHandle);

		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Triggered, this,
		                                   &ABdCharacterHero::input_Interaction);
		EnhancedInputComponent->BindAction(IA_Weapons, ETriggerEvent::Started, this,
		                                   &ABdCharacterHero::Input_WeaponList);
		EnhancedInputComponent->BindAction(IA_Weapons, ETriggerEvent::Completed, this,
		                                   &ABdCharacterHero::Input_WeaponListReleased);

		EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Started, this,
		                                   &ABdCharacterHero::Input_Inventory);

		EnhancedInputComponent->BindAction(IA_Aim, ETriggerEvent::Started, this, &ABdCharacterHero::Input_Aim);
		EnhancedInputComponent->BindAction(IA_Aim, ETriggerEvent::Completed, this, &ABdCharacterHero::Input_UnAim);

		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this,
		                                   &ABdCharacterHero::JumpAbilityInputTriggeredHandle);
		// EnhancedInputComponent->BindAction(IA_Jump,ETriggerEvent::Completed,this,&ABdCharacterHero::JumpAbilityInputReleasedHandle);

		EnhancedInputComponent->BindAction(IA_SwitchWeapon, ETriggerEvent::Triggered, this,
		                                   &ABdCharacterHero::Input_SwitchWeapon);
		// EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Started, this, &ABdCharacterHero::Input_Reload);

		EnhancedInputComponent->BindAction(IA_Menu, ETriggerEvent::Started, this, &ABdCharacterHero::Input_Menu);

		EnhancedInputComponent->BindAction(IA_AbilityTest, ETriggerEvent::Started, this,
		                                   &ABdCharacterHero::TestAbilityInputTriggeredHandle);
		EnhancedInputComponent->BindAction(IA_AbilityTest, ETriggerEvent::Completed, this,
		                                   &ABdCharacterHero::TestAbilityInputReleasedHandle);
	}
}

void ABdCharacterHero::Input_Move(const FInputActionValue& InputValue)
{
	APlayerController* controller = Cast<APlayerController>(GetController());
	const FVector2d Value = InputValue.Get<FVector2d>();


	const FRotator MovementRotation(0.0f, controller->GetControlRotation().Yaw, 0.0f);
	AddMovementInput(MovementRotation.RotateVector(FVector::ForwardVector), Value.Y);
	AddMovementInput(MovementRotation.RotateVector(FVector::RightVector), Value.X);
	// GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red,TEXT("走两步"));
}

void ABdCharacterHero::input_Lookup(const FInputActionValue& InputValue)
{
	if (bActivateMenu || bActivateInventory || bActivateBuffSelect || bActivateWeaponSwitch)return;
	APlayerController* controller = Cast<APlayerController>(GetController());
	const FVector2d Value = InputValue.Get<FVector2d>();
	controller->AddYawInput(Value.X);
	controller->AddPitchInput(-1 * Value.Y);
	// GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,Value.ToString());
	// GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,controller->GetControlRotation().ToString());
}


void ABdCharacterHero::input_Interaction(const FInputActionValue& InputValue)
{
	InteractionComponent->Interact();
}

void ABdCharacterHero::Input_Aim(const FInputActionValue& InputValue)
{
	if (WeaponState != EWeaponState::No_Weapon)
	{
		OnChangeAimingState.Broadcast(true);
		SpringArmComponent->TargetArmLength = 100;
		bIsAiming = true;
		bUseControllerRotationYaw = true;
		SpringArmComponent->SetRelativeTransform(FTransform(FVector(0, 0, 60)));
	}
}

void ABdCharacterHero::Input_UnAim(const FInputActionValue& InputValue)
{
	if (WeaponState != EWeaponState::No_Weapon)
	{
		OnChangeAimingState.Broadcast(false);
		SpringArmComponent->TargetArmLength = 300;
		bIsAiming = false;
		bUseControllerRotationYaw = false;
		SpringArmComponent->SetRelativeTransform(FTransform(FVector(0, 0, 50)));
	}
}


void ABdCharacterHero::Input_SwitchWeapon(const FInputActionValue& InputValue)
{
	if (bActivateWeaponSwitch)
	{
		WeaponSwitchUI->Rotate(InputValue.Get<float>());
		UKismetSystemLibrary::PrintString(this, "旋转" + FString::SanitizeFloat(InputValue.Get<float>()));
	}
}

void ABdCharacterHero::Input_WeaponList(const FInputActionValue& InputValue)
{
	if (!(bActivateBuffSelect || bActivateWeaponSwitch))
	{
		bActivateWeaponSwitch = true;
		WeaponSwitchUI->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABdCharacterHero::Input_WeaponListReleased(const FInputActionValue& InputValue)
{
	bActivateWeaponSwitch = false;
	WeaponSwitchUI->SetVisibility(ESlateVisibility::Hidden);
	if (WeaponSwitchUI->GetCurrentWeapon())
	{
		Set_Weapon(WeaponSwitchUI->GetCurrentWeapon());
	}
}

void ABdCharacterHero::Input_Inventory(const FInputActionValue& InputValue)
{
	if (!(bActivateBuffSelect || bActivateWeaponSwitch))
	{
		if (bActivateInventory)
		{
			InventoryUI->Deactivate();
		}
		else
		{
			InventoryUI->Activate();
		}
		bActivateInventory = !bActivateInventory;
	}
}

void ABdCharacterHero::Input_Menu(const FInputActionValue& InputValue)
{
	if (bActivateInventory)
	{
		InventoryUI->Deactivate();
		bActivateInventory = false;
	}
	else if (bActivateMenu)
	{
		MenuUI->Deactivate();
		bActivateMenu = false;
	}
	else if (bActivateBuffSelect)
	{
		return;
	}
	else if (!bActivateMenu)
	{
		bActivateMenu = true;
		MenuUI->Activate();
	}
}

FVector ABdCharacterHero::GetCameraLocation()
{
	return CameraComponent->GetComponentLocation();
}

bool ABdCharacterHero::Is_Armed()
{
	return !(WeaponState == EWeaponState::No_Weapon);
}

UBdWeaponSwitchUI* ABdCharacterHero::GetWeaponUI()
{
	return WeaponSwitchUI;
}

UActorComponent* ABdCharacterHero::GetInventoryComponent()
{
	return InventoryComponent;
}

ABdWeaponBase* ABdCharacterHero::GetMainWeapon()
{
	return MainWeapon;
}

TArray<ABdWeaponBase*> ABdCharacterHero::GetWeaponList()
{
	return InventoryComponent->GetWeaponList();
}

UAbilitySystemComponent* ABdCharacterHero::GetAbilitySystemComponent()
{
	if (GetPlayerState())
	{
		return Cast<ABdPlayerState>(GetPlayerState())->GetAbilitySystemComponent();
	}
	return nullptr;
}

void ABdCharacterHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ABdPlayerState* PS = GetPlayerState<ABdPlayerState>();
	if (Cast<ABdPlayerController>(NewController))
	{
		AbilitySystemComponent = Cast<UBdAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		HealthAttributes = PS->GetHealthAttributeSet();
		WeaponAttributes = PS->GetWeaponAttributeSet();
		CombatAttributes = PS->GetCombatAttributeSet();

		if (TestStartupAbility)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(TestStartupAbility, 1, 0, this));
		}

		//初始化所有初始技能
		for (TSubclassOf<UBdGameplayAbility> Ability : StartupAbilities)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
		}
		InitializeAttributes();

		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

ABdWeaponBase* ABdCharacterHero::GetPrimaryWeapon()
{
	return MainWeapon;
}

bool ABdCharacterHero::Set_Weapon(ABdEquipment* Weapon)
{
	// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,TEXT("changeweaponstate"));
	if (Weapon == MainWeapon)
	{
		// UKismetSystemLibrary::PrintString(this,"重复装备");
	}
	else
	{
		Weapon->SetEquiper(this);
		if (MainWeapon)
		{
			MainWeapon->UnEquipFromInventory_Implementation();
		}
		MainWeapon = Cast<ABdWeaponBase>(Weapon);
		MainWeapon->EquipFromInventory_Implementation();
	}
	WeaponState = EWeaponState::Primary_Weapon;
	OnChangeWeaponState.Broadcast(WeaponState, Ammos, AmmoMax, AmmoRemain);

	return true;
}

void ABdCharacterHero::Set_WeaponState(EWeaponState NewState)
{
	WeaponState = NewState;
}

ABdAmmoBase* ABdCharacterHero::Primary_Attack()
{
	ABdAmmoBase* res = nullptr;
	if (WeaponState != EWeaponState::No_Weapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black,TEXT("步枪攻击"));
		MainWeapon->Shoot();
		SetActorRotation(GetControlRotation());
		OnChangeWeaponState.Broadcast(WeaponState, Ammos, AmmoMax, AmmoRemain);
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
		for (auto Weapon : InventoryComponent->GetWeaponList())
		{
			QueryParams.AddIgnoredActor(Weapon);
		}
		QueryParams.AddIgnoredActor(this->MainWeapon);

		FVector StartLocation = CameraComponent->GetComponentLocation();
		FVector EndLocation = StartLocation + GetControlRotation().Vector() * 5000;
		//碰撞检测以及spawn--------------------------------------------------------------------
		FHitResult HitResult;
		if (GetWorld()->SweepSingleByObjectType(HitResult, StartLocation, EndLocation, FQuat::Identity,
		                                        ObjectQueryParams, CollsionSphere, QueryParams))
		{
			EndLocation = HitResult.ImpactPoint;
		}
		//spawn相关参数设置--------------------------------------------------------------------
		FVector WeaponLocation = GetMesh()->GetSocketLocation("weapon_r");
		FRotator Rotation = FRotationMatrix::MakeFromX(EndLocation - WeaponLocation).Rotator();
		FTransform SpawnTM = FTransform(Rotation, WeaponLocation);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;

		res = Cast<ABdAmmoBase>(GetWorld()->SpawnActor<AActor>(MainWeapon->GetAmmoClass(), SpawnTM, SpawnParameters));
		UKismetSystemLibrary::PrintString(this, res ? "spawn success" : "spawn fail");
		//发射弹丸结束----------------------------------------------------------------------------
	}
	return res;
}

void ABdCharacterHero::TestAddCritical(float Value)
{
	//控制台指令，增加相应数值的暴击率
	CombatAttributes->SetCriticalRate(CombatAttributes->GetCriticalRate() + Value);
}

void ABdCharacterHero::TestAddAttack(float Value)
{
	//控制台指令，增加相应数值的攻击率
	CombatAttributes->SetCriticalRate(CombatAttributes->GetCriticalRate() + Value);
}

void ABdCharacterHero::TestAddHealth(float Value)
{
	//控制台指令，增加相应数值的生命值
	HealthAttributes->SetHealth(HealthAttributes->GetHealth() + Value);
}

void ABdCharacterHero::TestAddMaxHealth(float Value)
{
	//控制台指令，增加相应数值的最大生命值
	CombatAttributes->SetCriticalRate(HealthAttributes->GetMaxHealth() + Value);
}

void ABdCharacterHero::TestAbilityInputTriggeredHandle()
{
	UKismetSystemLibrary::PrintString(this,TEXT("激活测试能力"));
	SendLocalInputToASC(true, EAbilityInputID::IA_AbilityTest);
}

void ABdCharacterHero::TestAbilityInputReleasedHandle()
{
	UKismetSystemLibrary::PrintString(this, TEXT("release测试能力"));
	SendLocalInputToASC(false, EAbilityInputID::IA_AbilityTest);
}

void ABdCharacterHero::JumpAbilityInputTriggeredHandle()
{
	UKismetSystemLibrary::PrintString(this,TEXT("跳跃"));
	SendLocalInputToASC(true, EAbilityInputID::IA_AbilityJump);
}

void ABdCharacterHero::JumpAbilityInputReleasedHandle()
{
	UKismetSystemLibrary::PrintString(this,TEXT("跳跃结束"));
	SendLocalInputToASC(false, EAbilityInputID::IA_AbilityJump);
}

void ABdCharacterHero::AttackAbilityInputTriggeredHandle()
{
	if (WeaponState != EWeaponState::No_Weapon)
	{
		UKismetSystemLibrary::PrintString(this,TEXT("突突突"));
		SendLocalInputToASC(true, EAbilityInputID::IA_AbilityAttack);
	}
}

void ABdCharacterHero::AttackAbilityInputReleasedHandle()
{
	if (WeaponState != EWeaponState::No_Weapon)
	{
		SendLocalInputToASC(false, EAbilityInputID::IA_AbilityAttack);
	}
}

void ABdCharacterHero::ReloadAbilityInputTriggeredHandle()
{
	if (WeaponState != EWeaponState::No_Weapon)
	{
		SendLocalInputToASC(true, EAbilityInputID::IA_AbilityReload);
	}
}

void ABdCharacterHero::ReloadAbilityInputReleasedHandle()
{
	if (WeaponState != EWeaponState::No_Weapon)
	{
		SendLocalInputToASC(false, EAbilityInputID::IA_AbilityReload);
	}
}

void ABdCharacterHero::SendLocalInputToASC(bool bIsPressed, EAbilityInputID InputID)
{
	if (AbilitySystemComponent)
	{
		if (bIsPressed)
		{
			AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(InputID));
		}
		else
		{
			AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(InputID));
		}
	}
}

void ABdCharacterHero::InitializeWeaponUI()
{
	ABdPlayerController* PC = Cast<ABdPlayerController>(GetController());
	if (WeaponSwitchUIClass)
	{
		WeaponSwitchUI = CreateWidget<UBdWeaponSwitchUI>(PC, WeaponSwitchUIClass);

		if (WeaponSwitchUI)
		{
			UKismetSystemLibrary::PrintString(this, "weapon list success");
			WeaponSwitchUI->OwningCharacter = this;
			WeaponSwitchUI->SetUpListen();

			WeaponSwitchUI->SetVisibility(ESlateVisibility::Hidden);
			WeaponSwitchUI->AddToViewport(0);
		}
	}
}

void ABdCharacterHero::InitializeInventoryUI()
{
	ABdPlayerController* PC = Cast<ABdPlayerController>(GetController());
	if (InventoryUIClass)
	{
		InventoryUI = CreateWidget<UBdInventoryUI>(PC, InventoryUIClass);

		if (InventoryUI)
		{
			InventoryUI->OwningCharacter = this;
			InventoryUI->SetUpListen();

			InventoryUI->SetVisibility(ESlateVisibility::Hidden);
			InventoryUI->AddToViewport(0);
		}
	}
}

void ABdCharacterHero::InitializeMenuUI()
{
	ABdPlayerController* PC = Cast<ABdPlayerController>(GetController());
	if (MenuUIClass)
	{
		MenuUI = CreateWidget<UBdMenuUI>(PC, MenuUIClass);

		if (MenuUI)
		{
			MenuUI->OwningCharacter = this;
			MenuUI->SetVisibility(ESlateVisibility::Hidden);
			MenuUI->AddToViewport(0);
		}
	}
}

void ABdCharacterHero::InitializeUI()
{
	this->InitializeWeaponUI();
	this->InitializeInventoryUI();
	this->InitializeMenuUI();
}

void ABdCharacterHero::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttributes();
	InitializeUI();
}
