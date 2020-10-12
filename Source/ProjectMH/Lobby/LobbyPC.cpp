// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"

#include "LobbyWidgetBase.h"
#include "../Basic/PartyWidgetBase.h"

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	if (LobbyWidgetClass)
	{
		if (IsLocalPlayerController())
		{
			LobbyWidgetObject = CreateWidget<ULobbyWidgetBase>(this, LobbyWidgetClass);
			LobbyWidgetObject->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
			//			SetInputMode(FInputModeUIOnly());
		}
	}

	if (PartyWidgetClass)
	{

		if (IsLocalPlayerController())
		{
			PartyWidgetObject = CreateWidget<UPartyWidgetBase>(this, PartyWidgetClass);
			PartyWidgetObject->AddToViewport();
			PartyWidgetObject->SetPlayerCount(1);
			PartyWidgetObject->AddSlots(1);
			HideParty();
		}
	}
}

void ALobbyPC::C2S_SendMessage_Implementation(const FText & Message)
{
	//c++ 11
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		if (PC)
		{
			//Server to Client
			PC->S2C_SendMessage(Message);
		}
	}
}

void ALobbyPC::S2C_SendMessage_Implementation(const FText & Message)
{
	if (LobbyWidgetObject)
	{
		LobbyWidgetObject->AddMessage(Message);
	}
}

void ALobbyPC::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogClass, Warning, TEXT("SetupInputComponent"));
	InputComponent->BindAction(TEXT("Party"), IE_Released, this, &ALobbyPC::ToggleParty);
}

void ALobbyPC::ToggleParty()
{
	UE_LOG(LogClass, Warning, TEXT("ToggleParty"));
	if (PartyWidgetObject)
	{
		if (PartyWidgetObject->GetVisibility() == ESlateVisibility::Visible)
		{

			HideParty();
			UE_LOG(LogClass, Warning, TEXT("HideParty"));
		}
		else
		{
			ShowParty();
			UE_LOG(LogClass, Warning, TEXT("ShowParty"));
		}

	}
}

void ALobbyPC::ShowParty()
{
	if (PartyWidgetObject)
	{
		PartyWidgetObject->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
		//		SetInputMode(FInputModeGameAndUI());
	}
}

void ALobbyPC::HideParty()
{
	if (PartyWidgetObject)
	{
		PartyWidgetObject->SetVisibility(ESlateVisibility::Collapsed);
	}
}


