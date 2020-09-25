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
	FString GetUserNickName();

	void SetUserNickName(FString NewUserNickName);


protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserNickName;
};
