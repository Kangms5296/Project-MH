// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHUDBase.h"
#include "Components/ScrollBox.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PartySlotInfoWidgetBase.h"
#include "../../MHGameInstance.h"
#include "Kismet/GameplayStatics.h"

//#include "../BattleGM.h"
//#include "../BattlePC.h"

void UBattleHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	T_InfoOutput = Cast<UScrollBox>(GetWidgetFromName(TEXT("T_InfoOutput")));
	HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP")));
	Stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("Stamina")));
	WeaponType = Cast<UImage>(GetWidgetFromName(TEXT("WeaponType")));
	WeaponCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponCount")));

	HideWeaponInfo();
}

void UBattleHUDBase::SetHP(float NewRatio)
{
	if (HP)
	{
		HP->SetPercent(NewRatio);
	}
}

void UBattleHUDBase::SetStamina(float NewRatio)
{
	if (Stamina)
	{
		Stamina->SetPercent(NewRatio);
	}
}

void UBattleHUDBase::SetCount(FString NewCount)
{
	if (WeaponCount)
	{
		WeaponCount->SetText(FText::FromString(NewCount));
	}
}

void UBattleHUDBase::ShowWeaponInfo()
{
	if (WeaponType)
	{
		WeaponType->SetVisibility(ESlateVisibility::Visible);
	}
	if (WeaponCount)
	{
		WeaponCount->SetVisibility(ESlateVisibility::Visible);
	}
}

void UBattleHUDBase::HideWeaponInfo()
{
	if (WeaponType)
	{
		WeaponType->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (WeaponCount)
	{
		WeaponCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBattleHUDBase::InitSlot()
{
	for (int i = 0; i < T_InfoOutput->GetChildrenCount(); ++i)
	{
		UPartySlotInfoWidgetBase* PartySlotInfo = Cast<UPartySlotInfoWidgetBase>(T_InfoOutput->GetChildAt(i));
		if (PartySlotInfo)
		{
			PartySlotInfo->bUse = false;
			PartySlotInfo->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UBattleHUDBase::PartySetting(const TArray<FString>& PartyArray)
{
	InitSlot();
	UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	for (int i = 0; i < PartyArray.Num(); ++i)
	{
		UPartySlotInfoWidgetBase* PartySlotInfo = Cast<UPartySlotInfoWidgetBase>(T_InfoOutput->GetChildAt(i));
		if (!(GI->GetUserID() == PartyArray[i]))
		{
			PartySlotInfo->bUse = true;
			PartySlotInfo->SetUserInfoID(PartyArray[i]);
			PartySlotInfo->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

//이함수 들어오면 터짐
void UBattleHUDBase::UIHP(float TempHP, const FString & ID)
{
	for (int i = 0; i < T_InfoOutput->GetChildrenCount(); ++i)
	{
		UPartySlotInfoWidgetBase* PartySlotInfo = Cast<UPartySlotInfoWidgetBase>(T_InfoOutput->GetChildAt(i));
		if (PartySlotInfo)
		{
			if (PartySlotInfo->T_UserInfoID->GetText().ToString() == ID)
			{
				PartySlotInfo->SetUserInfoHP(TempHP);
			}
		}
	}
}

/*
void UPartyWidgetBase::Ready(const FString & ID)
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (B_Start->GetVisibility() == ESlateVisibility::Visible)
	{
		PC->HideStart();
	}
	for (int i = 0; i < T_PartyOutput->GetChildrenCount(); ++i)
	{
		UPartySlotBase* PartySlot = Cast<UPartySlotBase>(T_PartyOutput->GetChildAt(i));
		if (PartySlot)
		{
			if (PartySlot->T_UserID->GetText().ToString() == ID)
			{
				if (PartySlot->T_UserReady->GetText().ToString() == FString(TEXT("UnReady")))
				{
					PartySlot->SetUserReady(true);
				}
				else if (PartySlot->T_UserReady->GetText().ToString() == FString(TEXT("Ready")))
				{
					PartySlot->SetUserReady(false);
				}
			}
		}
	}
}
*/