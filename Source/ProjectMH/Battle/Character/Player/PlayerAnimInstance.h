// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../Item/ItemDataTable.h"
#include "PlayerAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTMH_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Status")
	float Speed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Status")
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsFire : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsSprint : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsIronsight : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsCrouched : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint64 bIsJumping : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Status")
	float AimYaw;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Status")
	float AimPitch;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Status")
	float bIsReload;
};
