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
	B_Player = Cast<UButton>(GetWidgetFromName(TEXT("B_Player")));
}

void UPartySlotBase::SetUserInfo()
{
	UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	T_UserNN->SetText(FText::FromString(GI->GetUserNN()));
	T_UserID->SetText(FText::FromString(GI->GetUserID()));
}
