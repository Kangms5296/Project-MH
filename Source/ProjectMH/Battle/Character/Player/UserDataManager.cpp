// Fill out your copyright notice in the Description page of Project Settings.


#include "UserDataManager.h"
#include "../../../JsonHelper.h"
#include "UserData.h"

#include "Serialization/JsonWriter.h"
#include "Templates/SharedPointer.h"


void UUserDataManager::LoadUserDatasFromFile(FString SavedPath)
{
	FString OutputString = UJsonHelper::GetInstance()->LoadFromFile(SavedPath);
	auto JsonArr = UJsonHelper::GetInstance()->GetArrayField(OutputString, "Users");

	for (int i = 0; i < JsonArr.Num(); i++)
	{
		UUserData* Data = NewObject<UUserData>();
		Data->JsonToData(JsonArr[i]->AsObject());

		UserDatas.Add(Data);
	}
}

void UUserDataManager::SaveUserDatasToFile(FString SavePath)
{
	// Make JsonObject Array
	TArray<TSharedPtr<FJsonValue>> JsonArr;
	for (int i = 0; i < UserDatas.Num(); i++)
	{
		auto UserData = UserDatas[i]->DataToJson();
		TSharedRef< FJsonValueObject > JsonValue = MakeShareable(new FJsonValueObject(UserData));

		JsonArr.Add(JsonValue);
	}

	// JsonArray To String
	UJsonHelper::GetInstance()->StartMake();
	UJsonHelper::GetInstance()->AddArrayField("Users", JsonArr);
	FString OutputString = UJsonHelper::GetInstance()->EndMake();

	// Save File
	UJsonHelper::GetInstance()->SaveToFile(OutputString, SavePath);
}

void UUserDataManager::AddUser(UUserData * NewData)
{
	UserDatas.Add(NewData);
}

void UUserDataManager::DeleteUser(FString UserID)
{
	for (int i = 0; i < UserDatas.Num(); i++)
	{
		if (UserDatas[i]->UserID == UserID)
		{
			UserDatas.RemoveAt(i);
		}
	}
}

bool UUserDataManager::ExistUser(FString UserID)
{
	for (int i = 0; i < UserDatas.Num(); i++)
	{
		if (UserDatas[i]->UserID == UserID)
		{
			return true;
		}
	}
	return false;
}

UUserData * UUserDataManager::GetUser(FString UserID)
{
	for (int i = 0; i < UserDatas.Num(); i++)
	{
		if (UserDatas[i]->UserID == UserID)
		{
			return UserDatas[i];
		}
	}
	
	return nullptr;
}
