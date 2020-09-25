// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UUserData : public UObject
{
	GENERATED_BODY()
	
public:
	TSharedPtr<FJsonObject> DataToJson();
	void JsonToData(TSharedPtr<FJsonObject> Json);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString UserID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString UserPW;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString UserNN;

	// Add below
};
