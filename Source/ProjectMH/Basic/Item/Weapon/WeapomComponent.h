// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "../../../Battle/Item/ItemDataTable.h"
#include "WeapomComponent.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTMH_API UWeapomComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	bool IsArmWeapon;

	UPROPERTY()
	FItemDataTable CurrentWeaponData;

	class UInventorySlotWidgetBase* UsingSlot;

	// if weapon is Gun
	class UParticleSystem* MuzzleFlash;
};
