// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserDataManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UUserDataManager : public UObject
{
	GENERATED_BODY()


public:
	UPROPERTY()
	TArray<class UUserData*> UserDatas;  // ����Ǿ� �ִ� �������� ������ ĳ��

	UPROPERTY()
	FString SavePath;					// ���� ���

	void SetFilePath(FString Path);

	void LoadUserDatasFromFile();
	void SaveUserDatasToFile();

	void AddUser(class UUserData* NewData);
	void DeleteUser(FString UserID);
	bool ExistUser(FString UserID);
	class UUserData* GetUser(FString UserID);
};
