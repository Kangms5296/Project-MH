// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "LobbyGS.h"
#include "LobbyPC.h"
#include "../MHGameInstance.h"
#include "Kismet/GameplayStatics.h"


void ALobbyGM::GetUser(const FString & ID)
{
	PartySlots.Emplace(ID);
	PartySlots.Sort();
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		if (PC)
		{
			PC->Client_PartySet(PartySlots);
		}
	}
}

void ALobbyGM::GetReady(const FString & ID)
{
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		if (PC)
		{
			PC->Client_ReadySet(ID);
		}
	}
}

void ALobbyGM::StartGame()
{
	GetWorld()->ServerTravel(TEXT("FinalBattle"));
}
