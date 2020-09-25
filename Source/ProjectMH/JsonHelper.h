// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JsonHelper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UJsonHelper : public UObject
{
	GENERATED_BODY()

private:
	static UJsonHelper* Instance;

	class TSharedPtr<class FJsonObject> JsonStr;
public:
	static void Init();
	static UJsonHelper* GetInstance();

	void SaveToFile(FString Json, FString Path); // File�� ���� JSON ����.
	void SaveToFile_Append(FString Json, FString Path); // File �ۼ� ���� �ڷ� Json�� �߰�. 
	FString LoadFromFile(FString Path); // File���� JSON ĳ��

	void StartMake(); // ���ο� JSON ����.
	void AddStringField(FString Key, FString Value); // String Field �߰�.
	void AddArrayField(FString Key, TArray<class TSharedPtr<class FJsonValue>> Value); // Array Field �߰�.
	FString EndMake(); // ������ JSON ��ȯ.

	FString GetStringField(FString Json, FString Key); // �ش� Json����, Key�� �ش��ϴ� String �� ��ȯ
	TArray<class TSharedPtr<class FJsonValue>> GetArrayField(FString Json, FString Key); // �ش� Json����, Key�� �ش��ϴ� Array �� ��ȯ
};