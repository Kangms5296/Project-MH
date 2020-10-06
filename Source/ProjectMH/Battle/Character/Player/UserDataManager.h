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
	TArray<class UUserData*> UserDatas;  // 저장되어 있는 유저들의 데이터 캐싱

	void LoadUserDatasFromFile(FString SavedPath);
	void SaveUserDatasToFile(FString SavePath);

	void AddUser(class UUserData* NewData);
	void DeleteUser(FString UserID);
	bool ExistUser(FString UserID);
	class UUserData* GetUser(FString UserID);
};
