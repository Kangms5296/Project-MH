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

int UMHGameInstance::GetPartyNum()
{
	return PartyNum;
}

int UMHGameInstance::GetMaxPartyNum()
{
	return MaxPartyNum;
}

void UMHGameInstance::SetUserNN(FString NewUserNN)
{
	UserNN = NewUserNN;
}

void UMHGameInstance::SetUserID(FString NewUserID)
{
	UserID = NewUserID;
}

void UMHGameInstance::SetPartyNum(int Num)
{
	PartyNum = Num;
}

void UMHGameInstance::SetMaxPartyNum(int MaxNum)
{
	MaxPartyNum = MaxNum;
}

UJsonHelper* UMHGameInstance::GetJsonHelper()
{
	if (JsonHelper == nullptr)
	{
		JsonHelper = NewObject<UJsonHelper>();
	}

	return JsonHelper;
}
