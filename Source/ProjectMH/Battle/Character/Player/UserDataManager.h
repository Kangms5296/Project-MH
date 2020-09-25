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

private:
	static UUserDataManager* Instance;

	FString SavePath; // ���� ���

	TArray<class UUserData*> UserDatas; // ���ÿ� ����Ǿ� �ִ� �������� ������ ĳ��
public:
	static void Init();
	static UUserDataManager* GetInstance();

	void SetFilePath(FString Path);

	void LoadUserDatasFromFile();
	void SaveUserDatasToFile();

	void AddUser(class UUserData* NewData);
	void DeleteUser(FString UserID);
	bool ExistUser(FString UserID);
	class UUserData* GetUser(FString UserID);
};
