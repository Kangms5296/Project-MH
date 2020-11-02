// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySlotBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
//#include "Components/Border.h"
#include "../MHGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPartySlotBase::NativeConstruct()
{
	Super::NativeConstruct();
	//	I_ClassIcon = Cast<UBorder>(GetWidgetFromName(TEXT("I_ClassIcon")));
	T_UserNN = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_UserNN")));
	T_UserID = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_UserID")));
	T_UserReady = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_UserReady")));
	B_Player = Cast<UButton>(GetWidgetFromName(TEXT("B_Player")));
}

void UPartySlotBase::SetUserID(FString GetUserID)
{
	T_UserID->SetText(FText::FromString(GetUserID));
}

void UPartySlotBase::SetUserNN(FString GetUserNN)
{
	T_UserNN->SetText(FText::FromString(GetUserNN));
}

void UPartySlotBase::SetUserReady(bool Ready)
{
	if (Ready == true)
	{
		T_UserReady->SetText(FText::FromString(TEXT("Ready")));
	}
	else
	{
		T_UserReady->SetText(FText::FromString(TEXT("UnReady")));
	}
}
