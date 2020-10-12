// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "LobbyGS.h"

void ALobbyGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogClass, Warning, TEXT("PostLogin"));
	PlayerCount(true);
}

void ALobbyGM::Logout(AController * Exiting)
{
	PlayerCount(false);

	Super::Logout(Exiting);
}

void ALobbyGM::PlayerCount(bool user)
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		//		GS->PlayerCount++;
		if (user)
		{
			UE_LOG(LogClass, Warning, TEXT("Login Player1"));
			GS->PlayerCount++;
			GS->OnRep_PlayerCount(); //Host Only
			GS->AddPlayer();
			UE_LOG(LogClass, Warning, TEXT("Login Player2"));
		}
		else if (!user)
		{
			GS->PlayerCount--;
			GS->OnRep_PlayerCount(); //Host Only
//			GS->RemovePlayer();
		}
	}
}
