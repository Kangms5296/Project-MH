// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "Net/UnrealNetwork.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"
#include "../Basic/PartyWidgetBase.h"

void ALobbyGS::OnRep_PlayerCount()
{
	UE_LOG(LogClass, Warning, TEXT("PlayerCount1"));
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->PartyWidgetObject)
	{
		UE_LOG(LogClass, Warning, TEXT("PlayerCount2"));
		PC->PartyWidgetObject->SetPlayerCount(PlayerCount);
	}
}

void ALobbyGS::AddPlayer()
{
	UE_LOG(LogClass, Warning, TEXT("Add Player1"));
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->PartyWidgetObject)
	{
		UE_LOG(LogClass, Warning, TEXT("Add Player2"));
		PC->PartyWidgetObject->AddSlots(PlayerCount);
	}
}

void ALobbyGS::RemovePlayer()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->PartyWidgetObject)
	{
		PC->PartyWidgetObject->SetPlayerCount(PlayerCount);
	}
}

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, PlayerCount);
}
