// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonHelper.h"

#include "Serialization/JsonWriter.h"
#include "Templates/SharedPointer.h"



UJsonHelper* UJsonHelper::Instance;

void UJsonHelper::Init()
{
	Instance = NewObject<UJsonHelper>();
}

UJsonHelper * UJsonHelper::GetInstance()
{
	return Instance;
}

void UJsonHelper::SaveToFile(FString Json, FString Path)
{
	FFileHelper::SaveStringToFile(*Json, *Path);
}

void UJsonHelper::SaveToFile_Append(FString Json, FString Path)
{
	FFileHelper::SaveStringToFile(*Json, *Path, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

FString UJsonHelper::LoadFromFile(FString Path)
{
	FString Jsonstr;
	FFileHelper::LoadFileToString(Jsonstr, *Path);

	return Jsonstr;
}

void UJsonHelper::StartMake()
{
	JsonStr = MakeShareable(new FJsonObject);
}

void UJsonHelper::AddStringField(FString Key, FString Value)
{
	JsonStr->SetStringField(Key, Value);
}

void UJsonHelper::AddArrayField(FString Key, TArray<TSharedPtr<FJsonValue>> Value)
{
	JsonStr->SetArrayField(Key, Value);
}

FString UJsonHelper::EndMake()
{
	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonStr.ToSharedRef(), Writer);
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy< TCHAR >>> jsonObj = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy< TCHAR >>::Create(&OutputString);

	return OutputString;
}

FString UJsonHelper::GetStringField(FString Json, FString Key)
{
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(Json);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		return JsonObj->GetStringField(Key);
	}
	return "";
}

TArray<class TSharedPtr<class FJsonValue>> UJsonHelper::GetArrayField(FString Json, FString Key)
{
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(Json);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		return JsonObj->GetArrayField(Key);
	}

	return TArray<class TSharedPtr<class FJsonValue>>();
}
