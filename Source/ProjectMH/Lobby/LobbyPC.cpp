// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPC.h"
#include "LobbyGM.h"

#include "LobbyWidgetBase.h"
#include "../Basic/PartyWidgetBase.h"
#include "../MHGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (LobbyWidgetClass)
		{
			{
				LobbyWidgetObject = CreateWidget<ULobbyWidgetBase>(this, LobbyWidgetClass);
				LobbyWidgetObject->AddToViewport();

				bShowMouseCursor = true;
				SetInputMode(FInputModeGameAndUI());
			}
		}

		if (PartyWidgetClass)
		{
			PartyWidgetObject = CreateWidget<UPartyWidgetBase>(this, PartyWidgetClass);
			PartyWidgetObject->AddToViewport();
			HideParty();

			UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			Server_Party(GI->GetUserID());
		}
	}
}

void ALobbyPC::C2S_SendMessage_Implementation(const FText & Message)
{
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		if (PC)
		{
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
	InputComponent->BindAction(TEXT("Party"), IE_Released, this, &ALobbyPC::ToggleParty);
}

void ALobbyPC::ToggleParty()
{
	if (PartyWidgetObject)
	{
		if (PartyWidgetObject->GetVisibility() == ESlateVisibility::Visible)
		{

			HideParty();
		}
		else
		{
			ShowParty();
		}

	}
}

void ALobbyPC::ShowParty()
{
	if (PartyWidgetObject)
	{
		PartyWidgetObject->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
	}
}

void ALobbyPC::HideParty()
{
	if (PartyWidgetObject)
	{
		PartyWidgetObject->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ALobbyPC::ShowStart()
{
	if (HasAuthority())
	{
		if (PartyWidgetObject)
		{
			PartyWidgetObject->ShowStartGameButton();
		}
	}
}

void ALobbyPC::HideStart()
{
	if (HasAuthority())
	{
		if (PartyWidgetObject)
		{
			PartyWidgetObject->HideStartGameButton();
		}
	}
}

void ALobbyPC::Server_Party_Implementation(const FString & PartyID)
{
	ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->GetUser(PartyID);
	}
}

void ALobbyPC::Client_PartySet_Implementation(const TArray<FString>& PartySlotsID)
{
	if (IsLocalPlayerController() && PartyWidgetObject)
	{
		PartyWidgetObject->Party(PartySlotsID);
	}
}

void ALobbyPC::Server_Ready_Implementation(const FString & UserID)
{
	ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->GetReady(UserID);
	}
}

void ALobbyPC::Client_ReadySet_Implementation(const FString& UserSetID)
{
	if (IsLocalPlayerController() && PartyWidgetObject)
	{
		PartyWidgetObject->Ready(UserSetID);
	}
}
