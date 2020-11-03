// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySlotInfoWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "../../MHGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPartySlotInfoWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	T_UserInfoID = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_UserInfoID")));
	P_UserInfoHP = Cast<UProgressBar>(GetWidgetFromName(TEXT("P_UserInfoHP")));
}

void UPartySlotInfoWidgetBase::SetUserInfoID(FString GetUserID)
{
	T_UserInfoID->SetText(FText::FromString(GetUserID));
}

void UPartySlotInfoWidgetBase::SetUserInfoHP(float GetUserHP)
{
	P_UserInfoHP->SetPercent(GetUserHP);
}
