// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "../../../Basic/Item/Weapon/WeapomComponent.h"
#include "../../BattlePC.h"
#include "../../../Test/TestPC.h"
#include "MainWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "InventorySlotWidgetBase.h"
#include "../../../Basic/Item/Weapon/BulletBase.h"
#include "../../../Basic/Item/Weapon/DropItemBase.h"
#include "../../UI/BattleHUDBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameframeWork/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APlayerBase::APlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->SocketOffset = FVector(0, 40.0f, 88.f);
	SpringArm->TargetArmLength = 120.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));

	Weapon = CreateDefaultSubobject<UWeapomComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	NormalSpringArmPosition = SpringArm->GetRelativeLocation();
	CrouchedSpringArmPosition = NormalSpringArmPosition + FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() / 2);

	Tags.Add(TEXT("Player"));
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprint)
	{
		CurSprintGauge -= DeltaTime * 20;
		CurSprintGauge = FMath::Clamp(CurSprintGauge, 0.0f, MaxSprintGauge);
		if (CurSprintGauge <= 0.0f)
		{
			StopSprint();
		}

		ATestPC* PC = Cast<ATestPC>(GetController());
		if (PC && PC->BattleHUDObject)
		{
			PC->BattleHUDObject->SetStamina(CurSprintGauge / MaxSprintGauge);
		}
	}
	else
	{
		CurSprintGauge += DeltaTime * 5;
		CurSprintGauge = FMath::Clamp(CurSprintGauge, 0.0f, MaxSprintGauge);

		ATestPC* PC = Cast<ATestPC>(GetController());
		if (PC && PC->BattleHUDObject)
		{
			PC->BattleHUDObject->SetStamina(CurSprintGauge / MaxSprintGauge);
		}
	}
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerBase::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerBase::LookUp);

	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &APlayerBase::StartAttack);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &APlayerBase::StopAttack);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerBase::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &APlayerBase::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerBase::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerBase::StopSprint);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &APlayerBase::ToggleCrouch);

	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Pressed, this, &APlayerBase::StartIronsight);
	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Released, this, &APlayerBase::StopIronsight);

	PlayerInputComponent->BindAction(TEXT("Pickup"), IE_Pressed, this, &APlayerBase::Pickup);

	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &APlayerBase::Reload);

}

float APlayerBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentHP <= 0)
	{
		return 0.0f;
	}
	CurrentHP -= DamageAmount;
	CurrentHP = FMath::Clamp(CurrentHP, 0.0f, MaxHP);
	OnRep_CurrentHP();

	ATestPC* PC = Cast<ATestPC>(GetController());
	if (PC && PC->BattleHUDObject)
	{
		PC->BattleHUDObject->SetHP(CurrentHP / MaxHP);
	}

	if (CurrentHP <= 0)
	{
		// 사망 처리
		S2A_DeadAction(FMath::RandRange(1, 3));
	}
	else
	{
		// 피격 처리
		S2A_HitAction(FMath::RandRange(1, 4));
	}

	return CurrentHP;
}

void APlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerBase, bIsFire);
	DOREPLIFETIME(APlayerBase, bIsSprint);
	DOREPLIFETIME(APlayerBase, bIsReload);
	DOREPLIFETIME(APlayerBase, bIsIronsight);
	DOREPLIFETIME(APlayerBase, CurrentHP);
}

void APlayerBase::OnRep_CurrentHP()
{
	AController* PC = GetController();
	if (PC && PC->IsLocalController())
	{
		// Main UI HP Bar 반영
		ATestPC* TPC = Cast<ATestPC>(PC);
		if (TPC && TPC->MainWidgetObject)
		{

		}

		// 파티창 HP Bar에 반영


	}
}

void APlayerBase::MoveForward(float AxisValue)
{
	FRotator YawBaseRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector CameraForward = UKismetMathLibrary::GetForwardVector(YawBaseRotation);

	AddMovementInput(CameraForward, AxisValue);
}

void APlayerBase::MoveRight(float AxisValue)
{
	FRotator YawBaseRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector CameraRight = UKismetMathLibrary::GetRightVector(YawBaseRotation);

	AddMovementInput(CameraRight, AxisValue);
}

void APlayerBase::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerBase::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerBase::Sprint()
{
	bIsSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

	C2S_SetSprint(bIsSprint);
}

void APlayerBase::StopSprint()
{
	bIsSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	C2S_SetSprint(bIsSprint);
}

void APlayerBase::C2S_SetSprint_Implementation(bool State)
{
	bIsSprint = State;
	GetCharacterMovement()->MaxWalkSpeed = State ? SprintSpeed : WalkSpeed;
}

void APlayerBase::ToggleCrouch()
{
	if (GetCharacterMovement()->IsFalling())
		return;

	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void APlayerBase::StartAttack()
{
	switch (Weapon->CurrentWeaponData.WeaponType)
	{
	case EWeaponType::Unknown:
	{

		break;
	}

	case EWeaponType::Gun:
	{
		StartFire();
		break;
	}

	case EWeaponType::Sword:
	{

		break;
	}
	}
}

void APlayerBase::StopAttack()
{
	switch (Weapon->CurrentWeaponData.WeaponType)
	{
	case EWeaponType::Unknown:
	{

		break;
	}

	case EWeaponType::Gun:
	{
		StopFire();
		break;
	}

	case EWeaponType::Sword:
	{
		break;
	}
	}
}

void APlayerBase::C2S_SetFire_Implementation(bool State)
{
}

void APlayerBase::StartFire()
{
	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	bIsFire = true;
	OnFire();
}

void APlayerBase::OnFire()
{
	ATestPC* PC = Cast<ATestPC>(GetController());
	if (PC)
	{
		if (!bIsFire || GetCharacterMovement()->IsFalling() || bIsReload || Weapon->CurrentWeaponData.Value4 <= 0)
		{
			bIsFire = false;
			return;
		}
		
		// 총알 사용
		--(Weapon->CurrentWeaponData.Value4);
		if (PC->BattleHUDObject)
		{
			PC->BattleHUDObject->SetCount(FString::FromInt(Weapon->CurrentWeaponData.Value4) + " / " + FString::FromInt(Weapon->CurrentWeaponData.Value5));
		}

		int32 ScreenSizeX;
		int32 ScreenSizeY;
		FVector CrosshairWorldPosition; //3D
		FVector CrosshairWorldDirection; //3D 

		FVector CameraLocation;
		FRotator CameraRotation;

		//사람 반동
		int RandX = FMath::RandRange(-20, 20);
		int RandY = FMath::RandRange(3, 20);

		PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
		PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2 + RandX, ScreenSizeY / 2 + RandY, CrosshairWorldPosition, CrosshairWorldDirection);

		PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

		//총구 들리기(Tick에서 총 쏜 후에 애니메이션)
		FRotator PlayerRotation = GetControlRotation();
		PlayerRotation.Pitch += FMath::FRandRange(0.2f, 1.0f);
		GetController()->SetControlRotation(PlayerRotation);

		FVector TraceStart = CameraLocation;
		FVector TraceEnd = TraceStart + (CrosshairWorldDirection * 99999.f);

		C2S_ProcessFire(TraceStart, TraceEnd);
	}

	GetWorldTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&APlayerBase::OnFire,
		0.12f,
		false
	);
}

void APlayerBase::C2S_ProcessFire_Implementation(FVector TraceStart, FVector TraceEnd)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> Objects;

	Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(this);

	FHitResult OutHit;

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		TraceStart,
		TraceEnd,
		Objects,
		true,
		ActorToIgnore,
		EDrawDebugTrace::None,
		OutHit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.0f
	);

	if (Result)
	{
		//all client spawn Hiteffect and Decal
		S2A_SpawnHitEffectAndDecal(OutHit);

		//Point Damage
		UGameplayStatics::ApplyPointDamage(OutHit.GetActor(),
			Weapon->CurrentWeaponData.Value3,
			-OutHit.ImpactNormal,
			OutHit,
			GetController(),
			this,
			nullptr
		);

		MakeNoise(1.0f, this, OutHit.ImpactPoint);
	}

	//All Client Spawn Muzzleflash and Sound
	S2A_SpawnMuzzleFlashAndSound();
}

void APlayerBase::StopFire()
{
	bIsFire = false;
}

void APlayerBase::S2A_SpawnMuzzleFlashAndSound_Implementation()
{
	//WeaponSound and MuzzleFlash
	if (WeaponSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
			WeaponSound,
			Weapon->GetComponentLocation()
		);
	}

	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(
			MuzzleFlash,
			Weapon,
			TEXT("Muzzle"));
	}
}

void APlayerBase::S2A_SpawnHitEffectAndDecal_Implementation(FHitResult OutHit)
{
	//HitEffect(Blood) and Decal
	if (Cast<ACharacter>(OutHit.GetActor()))
	{
		//캐릭터
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			BloodHitEffect,
			OutHit.ImpactPoint + (OutHit.ImpactNormal * 10)
		);
	}
	else
	{
		//지형
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			HitEffect,
			OutHit.ImpactPoint + (OutHit.ImpactNormal * 10)
		);

		UDecalComponent* NewDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
			NormalDecal,
			FVector(5, 5, 5),
			OutHit.ImpactPoint,
			OutHit.ImpactNormal.Rotation(),
			10.0f
		);

		NewDecal->SetFadeScreenSize(0.005f);

	}
}

void APlayerBase::S2A_HitAction_Implementation(int Number)
{
	if (HitActionMontage)
	{
		FString SectionName = FString::Printf(TEXT("Hit%d"), Number);
		PlayAnimMontage(HitActionMontage, 1.0f, FName(SectionName));
	}
}

void APlayerBase::S2A_DeadAction_Implementation(int Number)
{
	if (DeadMontage)
	{
		FString SectionName = FString::Printf(TEXT("Death_%d"), Number);
		PlayAnimMontage(DeadMontage, 1.0f, FName(SectionName));
	}

	DisableInput(Cast<APlayerController>(GetController()));
}

void APlayerBase::C2S_SpawnBullet_Implementation(bool State)
{
	FVector ProjectileSpawnPos = Weapon->GetSocketLocation(TEXT("Muzzle"));

}

void APlayerBase::C2S_SetIronsight_Implementation(bool State)
{
	bIsIronsight = State;
}

void APlayerBase::StartIronsight()
{
	if (GetCharacterMovement()->IsFalling() || Weapon->CurrentWeaponData.WeaponType != EWeaponType::Gun)
		return;

	ATestPC* PC = Cast<ATestPC>(GetController());
	if (PC)
	{
		PC->MainWidgetObject->ShowCrosshair();
	}

	bIsIronsight = true;
	C2S_SetIronsight(true);
}

void APlayerBase::StopIronsight()
{
	ATestPC* PC = Cast<ATestPC>(GetController());
	if (PC)
	{
		PC->MainWidgetObject->HideCrosshair();
	}

	bIsIronsight = false;
	C2S_SetIronsight(false);
}

FRotator APlayerBase::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

void APlayerBase::C2S_SetReload_Implementation(bool newState)
{
	bIsReload = newState;
}

void APlayerBase::Reload()
{
	if (GetCharacterMovement()->IsFalling() || Weapon->CurrentWeaponData.WeaponType == EWeaponType::Unknown)
	{
		return;
	}

	bIsReload = true;
	C2S_SetReload(true);
}

void APlayerBase::ReloadEnd()
{
	ATestPC* PC = Cast<ATestPC>(GetController());
	if (PC && PC->BattleHUDObject)
	{
		Weapon->CurrentWeaponData.Value4 = Weapon->CurrentWeaponData.Value5;
		PC->BattleHUDObject->SetCount(FString::FromInt(Weapon->CurrentWeaponData.Value4) + " / " + FString::FromInt(Weapon->CurrentWeaponData.Value5));
	}
}

void APlayerBase::AddNearItem(ADropItemBase * AddItem)
{
	if (NearItemList.Num() > 0)
	{
		NearItemList[NearItemList.Num() - 1]->SetHighlight(false);
	}

	NearItemList.Add(AddItem);
	NearItemList[NearItemList.Num() - 1]->SetHighlight(true);
}

void APlayerBase::SubNearItem(ADropItemBase * SubItem)
{
	NearItemList[NearItemList.Num() - 1]->SetHighlight(false);
	NearItemList.Remove(SubItem);

	if (NearItemList.Num() > 0)
	{
		NearItemList[NearItemList.Num() - 1]->SetHighlight(true);
	}
}

void APlayerBase::Pickup()
{
	if (NearItemList.Num() > 0)
	{
		C2S_CheckPickupItem(NearItemList[NearItemList.Num() - 1]);
	}
}

void APlayerBase::C2S_CheckPickupItem_Implementation(ADropItemBase * NearItem)
{
	if (NearItem && !NearItem->IsPendingKill())
	{
		S2C_InsertItem(NearItem->ItemData);
		NearItem->Destroy();
	}
}

void APlayerBase::S2C_InsertItem_Implementation(FItemDataTable ItemData)
{
	ATestPC* PC = Cast<ATestPC>(GetController());
	if (PC && PC->IsLocalController())
	{
		PC->MainWidgetObject->InventoryObject->AddItem(ItemData, ItemData.Value1);
	}
}

void APlayerBase::UseItem(UInventorySlotWidgetBase* UseSlot, FItemDataTable ItemData)
{
	switch (ItemData.ItemType)
	{
	case EItemType::Consume:
	{
		C2S_RescueHP(ItemData.Value3);

		UseSlot->SubCount(1);
	}
	break;

	case EItemType::Equip:
	{
		switch (ItemData.WeaponType)
		{
		case EWeaponType::Gun:
		{
			// 사용중인 인벤토리 Slot에 표시
			if (UsingGunSlot != nullptr)
			{
				UsingGunSlot->UnDoHighlightSlotBG();
				UsingGunSlot->IsHighlight = false;
			}

			if (UsingGunSlot != UseSlot)
			{
				UsingGunSlot = UseSlot;
				UsingGunSlot->DoHighlightSlotBG();
				UsingGunSlot->IsHighlight = true;

				ArmWeapon(ItemData);

				ATestPC* PC = Cast<ATestPC>(GetController());
				if (PC && PC->BattleHUDObject)
				{
					PC->BattleHUDObject->SetCount(FString::FromInt(ItemData.Value4) + " / " + FString::FromInt(ItemData.Value5));
					PC->BattleHUDObject->ShowWeaponInfo();
				}
			}
			else
			{
				UsingGunSlot = nullptr;
				DisArmWeapon();

				ATestPC* PC = Cast<ATestPC>(GetController());
				if (PC && PC->BattleHUDObject)
				{
					PC->BattleHUDObject->HideWeaponInfo();
				}
			}
		}
		break;

		case EWeaponType::Sword:
		{
			// 사용중인 인벤토리 Slot에 표시
			if (UsingSwordSlot != nullptr)
			{
				UsingSwordSlot->UnDoHighlightSlotBG();
				UsingSwordSlot->IsHighlight = false;
			}

			if (UsingSwordSlot != UseSlot)
			{
				UsingSwordSlot = UseSlot;
				UsingSwordSlot->DoHighlightSlotBG();
				UsingSwordSlot->IsHighlight = true;

				ArmWeapon(ItemData);

				ATestPC* PC = Cast<ATestPC>(GetController());
				if (PC && PC->BattleHUDObject)
				{
					PC->BattleHUDObject->SetCount("00 / 00");
					PC->BattleHUDObject->ShowWeaponInfo();
				}
			}
			else
			{
				UsingSwordSlot = nullptr;
				DisArmWeapon();

				ATestPC* PC = Cast<ATestPC>(GetController());
				if (PC && PC->BattleHUDObject)
				{
					PC->BattleHUDObject->HideWeaponInfo();
				}
			}
		}
		break;

		}
	}
	break;

	}
}

void APlayerBase::C2S_RescueHP_Implementation(int RescueValue)
{
	CurrentHP += RescueValue;
	CurrentHP = FMath::Clamp(CurrentHP, 0.0f, MaxHP);
	OnRep_CurrentHP();

	S2A_SpawnRescueEffect();
}

void APlayerBase::S2A_SpawnRescueEffect_Implementation()
{
	if (RescueEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(
			RescueEffect,
			GetMesh());
	};

}

void APlayerBase::ArmWeapon(FItemDataTable ItemData)
{
	C2S_SetWeapon(true, ItemData);
}

void APlayerBase::DisArmWeapon()
{
	FItemDataTable TempData;
	TempData.WeaponType = EWeaponType::Unknown;

	C2S_SetWeapon(false, TempData);
}

void APlayerBase::C2S_SetWeapon_Implementation(bool NewState, FItemDataTable NewData)
{
	S2A_SetWeapon(NewState, NewData);
}

void APlayerBase::S2A_SetWeapon_Implementation(bool NewState, FItemDataTable NewData)
{
	if (NewState)
	{
		// 무기 장착
		FStreamableManager Loader;
		USkeletalMesh* TempMesh = Loader.LoadSynchronous<USkeletalMesh>(NewData.ItemSkeletalMesh);
		Weapon->SetSkeletalMesh(TempMesh);

		// 애니메이션 스테이트 머신 변경
		Weapon->CurrentWeaponData = NewData;
	}
	else
	{
		// 무기 해제
		Weapon->SetSkeletalMesh(nullptr);

		// 애니메이션 스테이트 머신 변경
		Weapon->CurrentWeaponData = NewData;
	}
}
