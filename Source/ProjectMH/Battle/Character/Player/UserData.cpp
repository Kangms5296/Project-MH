// Fill out your copyright notice in the Description page of Project Settings.


#include "UserData.h"

#include "Serialization/JsonWriter.h"
#include "Templates/SharedPointer.h"

TSharedPtr<FJsonObject> UUserData::DataToJson()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetStringField("UserID", UserID);
	JsonObject->SetStringField("UserPW", UserPW);
	JsonObject->SetStringField("UserNN", UserNN);

	return JsonObject;
}

void UUserData::JsonToData(TSharedPtr<FJsonObject> Json)
{
	UserID = Json->GetStringField("UserID");
	UserPW = Json->GetStringField("UserPW");
	UserNN = Json->GetStringField("UserNN");

	return;
}
