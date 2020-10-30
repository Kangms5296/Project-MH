// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Unknown = 0		UMETA(Display = "Unknown"),
	Consume = 1		UMETA(Display = "Consume"),
	Equip = 2		UMETA(Display = "Equip"),
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unknown = 0		UMETA(Display = "NoWeapon"),
	Gun = 1			UMETA(Display = "Gun"),
	Sword = 2		UMETA(Display = "Sword"),
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTMH_API FItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ItemIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemType ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemDesc;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TAssetPtr<class UTexture2D> ItemThumnail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TAssetPtr<class UStaticMesh> ItemStaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TAssetPtr<class USkeletalMesh> ItemSkeletalMesh;
};
