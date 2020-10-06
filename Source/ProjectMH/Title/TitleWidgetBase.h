// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UTitleWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	class UCanvasPanel* CurrentShowPanel;


	// === In Log-In Panel
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UCanvasPanel* P_LogIn;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* T_UserID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* T_Password;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UButton* B_LogIn;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UButton* B_SignUp;



	// === In Sigh-Up Panel
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UCanvasPanel* P_SignUp;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* T_NewUserID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* T_NewPassword;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* T_NewNICKNAME;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UButton* B_Create;



	// === In Server Panel
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UCanvasPanel* P_Server;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* T_ServerIP;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UButton* B_StartServer;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UButton* B_ConnectServer;
	


	//UMG Widget과 Control 변수 연결
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickLogInButton();

	UFUNCTION()
	void OnClickSignUpButton();

	UFUNCTION()
	void OnClickCreateButton();

	UFUNCTION()
	void OnClickStartServer();

	UFUNCTION()
	void OnClickConnectServer();

	void AddUserInfo(FString UserID, FString UserPW, FString UserNN);
	void DeleteUserInfo(FString UserID);

	void ShowLogInPanel();
	void ShowSignUpPanel();
	void ShowServerPanel();

	bool ExistID(FString UserID);
	bool ValidUserInfo(FString UserID, FString UserPW);

	void SaveToGI(FString UserID, FString UserNN);

	UPROPERTY()
	class UUserDataManager* UserDataManager;
};
