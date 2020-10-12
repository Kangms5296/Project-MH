// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidgetBase.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TitlePC.h"
#include "Kismet/GameplayStatics.h"
#include "../MHGameInstance.h"

#include "../Battle/Character/Player/UserDataManager.h"
#include "../Battle/Character/Player/UserData.h"

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

		B_ConnectServer = Cast<UButton>(GetWidgetFromName(TEXT("B_ConnectServer")));
		if (B_ConnectServer)
		{
			B_ConnectServer->OnClicked.AddDynamic(this, &UTitleWidgetBase::OnClickConnectServer);
		}
	}

	// ���Ͽ��� ���� ���� �����͸� ĳ��
	UserDataManager = NewObject<UUserDataManager>(this);
	UserDataManager->LoadUserDatasFromFile("C:\\UE\\Project\\Down\\Project-MH\\Content\\Data\\UserData\\UserData.txt");

	ShowLogInPanel();
}

void UTitleWidgetBase::OnClickLogInButton()
{
	// User ���� Ȯ��
	FString ID = T_UserID->GetText().ToString();
	FString PW = T_Password->GetText().ToString();
	if (ValidUserInfo(ID, PW))
	{
		UUserData* Data = UserDataManager->GetUser(ID);

		// GI�� ���� User ���� ����
		SaveToGI(ID, Data->UserNN);

		// ��Ʈ��ũ ���� �г� ǥ��
		ShowServerPanel();
	}
}

void UTitleWidgetBase::OnClickSignUpButton()
{
	// Sigh-UP ȭ������ �̵�
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

	// ������ �����Ϳ� ��
	FString ID = T_NewUserID->GetText().ToString();
	FString PW = T_NewPassword->GetText().ToString();
	FString NN = T_NewNICKNAME->GetText().ToString();
	if (!ExistID(ID))
	{
		// ���ο� User ������ ĳ�� ��Ͽ� �߰�
		AddUserInfo(ID, PW, NN);

		// Log-IN ȭ������ �̵�
		ShowLogInPanel();
	}
}

void UTitleWidgetBase::OnClickStartServer()
{
	//������ ����
	ATitlePC* PC = GetOwningPlayer<ATitlePC>();
	if (PC)
	{
		// ĳ�� ���� ������ ����
		UserDataManager->SaveUserDatasToFile("C:\\UE\\Project\\Down\\Project-MH\\Content\\Data\\UserData\\UserData.txt");

		// ���� ����
		PC->StartServer();
	}
}

void UTitleWidgetBase::OnClickConnectServer()
{
	//������ ����
	ATitlePC* PC = GetOwningPlayer<ATitlePC>();
	if (PC)
	{
		if (T_ServerIP)
		{
			// ĳ�� ���� ������ ����
			UserDataManager->SaveUserDatasToFile("C:\\UE\\Project\\Down\\Project-MH\\Content\\Data\\UserData\\UserData.txt");

			// ���� ����
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
	if (UserDataManager->ExistUser(UserID))
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

bool UTitleWidgetBase::ValidUserInfo(FString UserID, FString UserPW)
{
	UUserData* Data = UserDataManager->GetUser(UserID);
	if (Data && Data->UserPW == UserPW)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void UTitleWidgetBase::AddUserInfo(FString UserID, FString UserPW, FString UserNN)
{
	UUserData* Data = NewObject<UUserData>();

	Data->UserID = UserID;
	Data->UserPW = UserPW;
	Data->UserNN = UserNN;

	UserDataManager->AddUser(Data);
}

void UTitleWidgetBase::DeleteUserInfo(FString UserID)
{
	UserDataManager->DeleteUser(UserID);
}

void UTitleWidgetBase::SaveToGI(FString UserID, FString UserNN)
{
	UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->SetUserID(UserID);
		GI->SetUserNN(UserNN);
	}
}