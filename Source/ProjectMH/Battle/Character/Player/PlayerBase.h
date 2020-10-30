// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Item/ItemDataTable.h"
#include "PlayerBase.generated.h"

UCLASS()
class PROJECTMH_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UWeapomComponent* Weapon;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = "OnRep_CurrentHP", Category = "Data")
	float CurrentHP = 100.0f;

	UFUNCTION()
	void OnRep_CurrentHP();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	float MaxHP = 100.0f;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);

	void Sprint();
	void StopSprint();

	float CurSprintGauge = 100.0f;
	float MaxSprintGauge = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float WalkSpeed = 450.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SprintSpeed = 900.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Status")
	uint64 bIsSprint : 1;

	UFUNCTION(Server, Reliable)
	void C2S_SetSprint(bool State);
	void C2S_SetSprint_Implementation(bool State);

	void ToggleCrouch();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SpringArm")
	FVector NormalSpringArmPosition;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SpringArm")
	FVector CrouchedSpringArmPosition;

	void StartAttack();
	void StopAttack();

	FTimerHandle FireTimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Status")
	uint64 bIsFire : 1;

	UFUNCTION(Server, Reliable)
	void C2S_SetFire(bool State);
	void C2S_SetFire_Implementation(bool State);

	void StartFire();
	void OnFire();
	void StopFire();

	void C2S_SpawnBullet(bool State);
	void C2S_SpawnBullet_Implementation(bool State);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Status")
	uint64 bIsIronsight : 1;

	UFUNCTION(Server, Reliable)
	void C2S_SetIronsight(bool State);
	void C2S_SetIronsight_Implementation(bool State);

	void StartIronsight();
	void StopIronsight();

	FRotator GetAimOffset() const;

	UFUNCTION(Server, Reliable)
	void C2S_ProcessFire(FVector TraceStart, FVector TraceEnd);
	void C2S_ProcessFire_Implementation(FVector TraceStart, FVector TraceEnd);

	UFUNCTION(NetMulticast, Unreliable)
	void S2A_SpawnMuzzleFlashAndSound();
	void S2A_SpawnMuzzleFlashAndSound_Implementation();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class USoundBase* WeaponSound;

	UFUNCTION(NetMulticast, Unreliable)
	void S2A_SpawnHitEffectAndDecal(FHitResult OutHit);
	void S2A_SpawnHitEffectAndDecal_Implementation(FHitResult OutHit);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UParticleSystem* BloodHitEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UParticleSystem* HitEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UMaterialInstance* NormalDecal;

	UFUNCTION(NetMulticast, Reliable)
	void S2A_HitAction(int Number);
	void S2A_HitAction_Implementation(int Number);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UAnimMontage* HitActionMontage;

	UFUNCTION(NetMulticast, Reliable)
	void S2A_DeadAction(int Number);
	void S2A_DeadAction_Implementation(int Number);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UAnimMontage* DeadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ABulletBase> BulletClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Status")
	uint8 bIsReload : 1;

	UFUNCTION(Server, Reliable)
	void C2S_SetReload(bool newState);
	void C2S_SetReload_Implementation(bool newState);

	void Reload();
	void ReloadEnd();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UAnimMontage* ReloadMontage;

	TArray<class ADropItemBase*>NearItemList;
	void AddNearItem(class ADropItemBase* AddItem);
	void SubNearItem(class ADropItemBase* SubItem);

	void Pickup();

	UFUNCTION(Server, Reliable)
	void C2S_CheckPickupItem(class ADropItemBase* PickupItem);
	void C2S_CheckPickupItem_Implementation(class ADropItemBase* NearItem);

	UFUNCTION(Client, Reliable)
	void S2C_InsertItem(FItemDataTable ItemData);
	void S2C_InsertItem_Implementation(FItemDataTable ItemData);

	class UInventorySlotWidgetBase* UsingGunSlot;
	class UInventorySlotWidgetBase* UsingSwordSlot;
	void UseItem(class UInventorySlotWidgetBase* UseSlot, FItemDataTable ItemData);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	class UParticleSystem* RescueEffect;

	UFUNCTION(Server, Reliable)
	void C2S_RescueHP(int RescueValue);
	void C2S_RescueHP_Implementation(int RescueValue);

	UFUNCTION(NetMulticast, Reliable)
	void S2A_SpawnRescueEffect();
	void S2A_SpawnRescueEffect_Implementation();

	void ArmWeapon(FItemDataTable ItemData);
	void DisArmWeapon();

	UFUNCTION(Server, Reliable)
	void C2S_SetWeapon(bool NewState, FItemDataTable NewData);
	void C2S_SetWeapon_Implementation(bool NewState, FItemDataTable NewData);

	UFUNCTION(NetMulticast, Reliable)
	void S2A_SetWeapon(bool NewState, FItemDataTable NewData);
	void S2A_SetWeapon_Implementation(bool NewState, FItemDataTable NewData);
};
