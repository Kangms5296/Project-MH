// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MHGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UMHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FString GetUserNN();
	FString GetUserID();
	int GetPartyNum();
	int GetMaxPartyNum();

	void SetUserNN(FString NewUserNN);
	void SetUserID(FString NewUserID);
	void SetPartyNum(int Num);
	void SetMaxPartyNum(int MaxNum);

	class UJsonHelper* GetJsonHelper();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserNN;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PartyNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxPartyNum;

	UPROPERTY()
	class UJsonHelper* JsonHelper;
};
