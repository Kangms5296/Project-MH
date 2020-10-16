// Fill out your copyright notice in the Description page of Project Settings.


#include "MHGameInstance.h"
#include "JsonHelper.h"

FString UMHGameInstance::GetUserNN()
{
	return UserNN;
}

FString UMHGameInstance::GetUserID()
{
	return UserID;
}

void UMHGameInstance::SetUserNN(FString NewUserNN)
{
	UserNN = NewUserNN;
}

void UMHGameInstance::SetUserID(FString NewUserID)
{
	UserID = NewUserID;
}

UJsonHelper* UMHGameInstance::GetJsonHelper()
{
	if (JsonHelper == nullptr)
	{
		JsonHelper = NewObject<UJsonHelper>();
	}

	return JsonHelper;
}
