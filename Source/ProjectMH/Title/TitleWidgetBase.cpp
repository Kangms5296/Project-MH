// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidgetBase.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TitlePC.h"
#include "Kismet/GameplayStatics.h"
#include "../MHGameInstance.h"

#include "Serialization/JsonWriter.h"
#include "Templates/SharedPointer.h"

void UTitleWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();


	// === In Log-In Panel
	{
		P_LogIn = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("P_LogIn")));
		P_LogIn->SetVisibility(ESlateVisibility::Collapsed);

		T_UserID = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("T_UserID")));
		T_Password = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("T_Password")));
		
		B_LogIn = Cast<UButton>(GetWidgetFromName(TEXT("B_LogIn")));
		if (B_LogIn)
		{
			B_LogIn->OnClicked.AddDynamic(this, &UTitleWidgetBase::OnClickLogInButton);
		}

		B_SignUp = Cast<UButton>(GetWidgetFromName(TEXT("B_SignUp")));
		if (B_SignUp)
		{
			B_SignUp->OnClicked.AddDynamic(this, &UTitleWidgetBase::OnClickSignUpButton);
		}
	}


	// === In Sigh-Up Panel
	{
		P_SignUp = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("P_SignUp")));
		P_SignUp->SetVisibility(ESlateVisibility::Collapsed);

		T_NewUserID = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("T_NewUserID")));
		T_NewPassword = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("T_NewPassword")));
		T_NewNICKNAME = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("T_NewNICKNAME")));

		B_Create = Cast<UButton>(GetWidgetFromName(TEXT("B_Create")));
		if (B_Create)
		{
			B_Create->OnClicked.AddDynamic(this, &UTitleWidgetBase::OnClickCreateButton);
		}
	}


	// === In Server Panel
	{
		P_Server = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("P_Server")));
		P_Server->SetVisibility(ESlateVisibility::Collapsed);

		T_ServerIP = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("T_ServerIP")));

		B_StartServer = Cast<UButton>(GetWidgetFromName(TEXT("B_StartServer")));
		if (B_StartServer)
		{
			B_StartServer->OnClicked.AddDynamic(this, &UTitleWidgetBase::OnClickStartServer);
		}

		B_ConnenctServer = Cast<UButton>(GetWidgetFromName(TEXT("B_ConnenctServer")));
		if (B_ConnenctServer)
		{
			B_ConnenctServer->OnClicked.AddDynamic(this, &UTitleWidgetBase::OnClickConnectServer);
		}
	}

	ShowLogInPanel();
}

void UTitleWidgetBase::OnClickLogInButton()
{
	// User 정보 확인
	FString ID = T_UserID->GetText().ToString();
	FString PW = T_Password->GetText().ToString();
	if (ExistID(ID) && ValidUserInfo(ID, PW))
	{
		LoadUserInfo(ID);

		ShowServerPanel();
	}
}

void UTitleWidgetBase::OnClickSignUpButton()
{
	// Sigh-UP 화면으로 이동
	ShowSignUpPanel();
}

void UTitleWidgetBase::OnClickCreateButton()
{
	if (T_NewUserID->GetText().ToString().IsEmpty() ||
		T_NewPassword->GetText().ToString().IsEmpty() ||
		T_NewNICKNAME->GetText().ToString().IsEmpty())
	{
		return;
	}

	// 기존의 데이터와 비교
	FString ID = T_NewUserID->GetText().ToString();
	if (!ExistID(ID))
	{
		// 새로운 User 정보를 추가
		SaveUserInfo();

		// Log-IN 화면으로 이동
		ShowLogInPanel();
	}
}

void UTitleWidgetBase::OnClickStartServer()
{
	//서버를 시작
	ATitlePC* PC = GetOwningPlayer<ATitlePC>();
	if (PC)
	{
		PC->StartServer();
	}
}

void UTitleWidgetBase::OnClickConnectServer()
{
	//서버에 접속
	ATitlePC* PC = GetOwningPlayer<ATitlePC>();
	if (PC)
	{
		if (T_ServerIP)
		{
			FString ServerIPAddress = T_ServerIP->GetText().ToString();

			PC->ConnectServer(ServerIPAddress);
		}
	}
}

void UTitleWidgetBase::ShowLogInPanel()
{
	if (CurrentShowPanel)
	{
		CurrentShowPanel->SetVisibility(ESlateVisibility::Collapsed);
	}

	T_UserID->SetText(FText::FromString(TEXT("")));
	T_Password->SetText(FText::FromString(TEXT("")));

	P_LogIn->SetVisibility(ESlateVisibility::Visible);
	CurrentShowPanel = P_LogIn;
}

void UTitleWidgetBase::ShowSignUpPanel()
{
	if (CurrentShowPanel)
	{
		CurrentShowPanel->SetVisibility(ESlateVisibility::Collapsed);
	}

	T_NewUserID->SetText(FText::FromString(TEXT("")));
	T_NewPassword->SetText(FText::FromString(TEXT("")));
	T_NewNICKNAME->SetText(FText::FromString(TEXT("")));

	P_SignUp->SetVisibility(ESlateVisibility::Visible);
	CurrentShowPanel = P_SignUp;
}

void  UTitleWidgetBase::ShowServerPanel()
{
	if (CurrentShowPanel)
	{
		CurrentShowPanel->SetVisibility(ESlateVisibility::Collapsed);
	}

	P_Server->SetVisibility(ESlateVisibility::Visible);
	CurrentShowPanel = P_Server;
}

bool UTitleWidgetBase::ExistID(FString UserID)
{
	FString FilePath = "C:\\Users\\skill\\Desktop\\ProjectMH\\Content\\Data\\UserData\\" + UserID + ".txt";

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Good"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Bad"));
		return false;
	}
}

bool UTitleWidgetBase::ValidUserInfo(FString UserID, FString UserPW)
{
	FString Jsonstr;

	// Load Json
	FString FilePath = "C:\\Users\\skill\\Desktop\\ProjectMH\\Content\\Data\\UserData\\" + UserID + ".txt";
	FFileHelper::LoadFileToString(Jsonstr, *FilePath);

	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(Jsonstr);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		FString PW = JsonObj->GetStringField(TEXT("UserPW"));

		if (PW == UserPW)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void UTitleWidgetBase::SaveUserInfo()
{
	// Set JSON
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("UserID", T_NewUserID->GetText().ToString());
	JsonObject->SetStringField("UserPW", T_NewPassword->GetText().ToString());
	JsonObject->SetStringField("UserNN", T_NewNICKNAME->GetText().ToString());

	// Serialize(JSON to String)
	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy< TCHAR >>> jsonObj = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy< TCHAR >>::Create(&OutputString);

	// Save To File
	FString FilePath = "C:\\Users\\skill\\Desktop\\ProjectMH\\Content\\Data\\UserData\\" + T_NewUserID->GetText().ToString() + ".txt";
	FFileHelper::SaveStringToFile(*OutputString, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void UTitleWidgetBase::LoadUserInfo(FString UserID)
{
	FString Jsonstr;

	// Load Json
	FString FilePath = "C:\\Users\\skill\\Desktop\\ProjectMH\\Content\\Data\\UserData\\" + UserID + ".txt";
	FFileHelper::LoadFileToString(Jsonstr, *FilePath);

	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(Jsonstr);
	
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(Reader, JsonObj))
	{
		FString userID = JsonObj->GetStringField(TEXT("UserID"));
		FString userPW = JsonObj->GetStringField(TEXT("UserPW"));
		FString userNN = JsonObj->GetStringField(TEXT("UserNN"));

		SaveToGI(userNN);
	}
}

void UTitleWidgetBase::SaveToGI(FString UserNickName)
{
	UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->SetUserNickName(UserNickName);
	}
}