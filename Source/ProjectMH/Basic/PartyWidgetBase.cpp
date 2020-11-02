// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyWidgetBase.h"
#include "Components/ScrollBox.h"		//PartyOutput
#include "Components/Button.h"			//start,Ready Button
#include "PartySlotBase.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "../MHGameInstance.h"
#include "../Lobby/LobbyGM.h"
#include "../Lobby/LobbyPC.h"

void UPartyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	B_Start = Cast<UButton>(GetWidgetFromName(TEXT("B_Start")));
	if (B_Start)
	{
		B_Start->OnClicked.AddDynamic(this, &UPartyWidgetBase::PressStartButton);
	}

	B_Ready = Cast<UButton>(GetWidgetFromName(TEXT("B_Ready")));
	if (B_Ready)
	{
		B_Ready->OnClicked.AddDynamic(this, &UPartyWidgetBase::PressReadyButton);
	}

	T_PartyOutput = Cast<UScrollBox>(GetWidgetFromName(TEXT("T_PartyOutput")));
}

void UPartyWidgetBase::PressStartButton()
{
	for (int i = 0; i < T_PartyOutput->GetChildrenCount(); ++i)
	{
		UPartySlotBase* PartySlot = Cast<UPartySlotBase>(T_PartyOutput->GetChildAt(i));
		if (PartySlot)
		{
			if (PartySlot->T_UserReady->GetText().ToString() == FString(TEXT("UnReady")))
			{
				return;
			}
		}
	}

	int MaxCount = 0;
	for (int i = 0; i < T_PartyOutput->GetChildrenCount(); ++i)
	{
		UPartySlotBase* PartySlot = Cast<UPartySlotBase>(T_PartyOutput->GetChildAt(i));
		if (PartySlot)
		{
			if (PartySlot->GetVisibility() == ESlateVisibility::Visible)
			{
				++MaxCount;
			}
		}
	}
	for (int i = 0; i < MaxCount; ++i)
	{
		UPartySlotBase* PartySlot = Cast<UPartySlotBase>(T_PartyOutput->GetChildAt(i));
		if (PartySlot)
		{
			UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (GI)
			{
				GI->SetMaxPartyNum(MaxCount);
			}
		}
	}

	ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM) //Server Only
	{
		GM->StartGame();
	}
}

void UPartyWidgetBase::PressReadyButton()
{
	UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && GI)
	{
		PC->Server_Ready(GI->GetUserID());
	}
}

void UPartyWidgetBase::HideStartGameButton()
{
	if (B_Start)
	{
		B_Start->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPartyWidgetBase::ShowStartGameButton()
{
	if (B_Start)
	{
		B_Start->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPartyWidgetBase::InitSlot()
{
	for (int i = 0; i < T_PartyOutput->GetChildrenCount(); ++i)
	{
		UPartySlotBase* PartySlot = Cast<UPartySlotBase>(T_PartyOutput->GetChildAt(i));
		if (PartySlot)
		{
			PartySlot->bUse = false;
			PartySlot->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}


void UPartyWidgetBase::Party(const TArray<FString>& PartyArray)
{
	InitSlot();
	UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	for (int i = 0; i < PartyArray.Num(); ++i)
	{
		UPartySlotBase* PartySlot = Cast<UPartySlotBase>(T_PartyOutput->GetChildAt(i));
		PartySlot->bUse = true;
		PartySlot->Num = i;
		GI->SetPartyNum(PartySlot->Num);
		PartySlot->SetUserID(PartyArray[i]);
		//		PartySlot->SetUserID(FString::FromInt(PartySlot->Num));
		PartySlot->SetVisibility(ESlateVisibility::Visible);
		PartySlot->SetUserReady(false);
		B_Start->SetVisibility(ESlateVisibility::Collapsed);
	}
}

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

	for (int i = 0; i < T_PartyOutput->GetChildrenCount(); ++i)
	{
		UPartySlotBase* PartySlot = Cast<UPartySlotBase>(T_PartyOutput->GetChildAt(i));
		if (PartySlot)
		{
			if (PartySlot->T_UserReady->GetText().ToString() == FString(TEXT("UnReady")))
			{
				return;
			}
		}
	}
	PC->ShowStart();
}