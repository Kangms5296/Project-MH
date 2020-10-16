// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeapomComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unknown = 0		UMETA(Display = "Unknown"),
	Gun		= 1		UMETA(Display = "Gun"),
	Sword	= 2		UMETA(Display = "Sword"),
};


/**
 * 
 */
UCLASS()
class PROJECTMH_API UWeapomComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType WeaponType;
};
