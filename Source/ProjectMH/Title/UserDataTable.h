// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UserDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTMH_API FUserDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int UserIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserPassword;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserNickName;
};
