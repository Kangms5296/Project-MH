// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "../../../Basic/Item/Weapon/WeapomComponent.h"
#include "../../BattlePC.h"
#include "../../../Test/TestPC.h"
#include "MainWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "../../../Basic/Item/Weapon/BulletBase.h"
#include "../../../Basic/Item/Weapon/DropItemBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameframeWork/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerBase::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerBase::StopFire);

	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Pressed, this, &APlayerBase::StartIronsight);
	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Released, this, &APlayerBase::StopIronsight);

	PlayerInputComponent->BindAction(TEXT("Pickup"), IE_Pressed, this, &APlayerBase::Pickup);

	// PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &APlayerBase::Reload);

}

float APlayerBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentHP <= 0)
	{
		return 0.0f;
	}

	CurrentHP -= DamageAmount;
	OnRep_CurrentHP();

	CurrentHP = FMath::Clamp(CurrentHP, 0.0f, MaxHP);
	if (CurrentHP <= 0)
	{
		// 사망

	}
	else
	{
		// 피격
	}

	return CurrentHP;
}

void APlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerBase, bIsFire);
	DOREPLIFETIME(APlayerBase, bIsSprint);
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
	switch (Weapon->WeaponType)
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
	switch (Weapon->WeaponType)
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
	bIsFire = true;
	OnFire();
}

void APlayerBase::OnFire()
{
	if (!bIsFire)
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		int32 ScreenSizeX;
		int32 ScreenSizeY;
		PC->GetViewportSize(ScreenSizeX, ScreenSizeY);

		//int RandX = FMath::RandRange(-20, 20);
		//int RandY = FMath::RandRange(3, 20);
		FVector CrosshairWorldPosition; //3D
		FVector CrosshairWorldDirection; //3D 
		//PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2 + RandX, ScreenSizeY / 2 + RandY, CrosshairWorldPosition, CrosshairWorldDirection);
		PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2, ScreenSizeY / 2, CrosshairWorldPosition, CrosshairWorldDirection);

		FVector FirePos = Weapon->GetSocketLocation(TEXT("Muzzle"));
		FVector FireDir = CrosshairWorldDirection;

		GetWorld()->SpawnActor<AActor>(BulletClass, FirePos, FireDir.Rotation());
	}

	GetWorldTimerManager().SetTimer(FireTimerHandle,
		this,
		&APlayerBase::OnFire,
		0.12f,
		false);
}

void APlayerBase::StopFire()
{
	bIsFire = false;
}

void APlayerBase::C2S_SpawnBullet_Implementation(bool State)
{
	FVector ProjectileSpawnPos = Weapon->GetSocketLocation(TEXT("Muzzle"));

}

void APlayerBase::C2S_SetIronsight_Implementation(bool State)
{

}

void APlayerBase::StartIronsight()
{

}

void APlayerBase::StopIronsight()
{

}

FRotator APlayerBase::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
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
		PC->MainWidgetObject->InventoryObject->AddItem(ItemData, 1);
	}
}