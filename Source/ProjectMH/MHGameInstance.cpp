// Fill out your copyright notice in the Description page of Project Settings.


#include "MHGameInstance.h"

FString UMHGameInstance::GetUserNickName()
{
	return UserNickName;
}

void UMHGameInstance::SetUserNickName(FString NewUserNickName)
{
	UserNickName = NewUserNickName;
}
