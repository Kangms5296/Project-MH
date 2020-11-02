// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGM.h"
#include "BattlePC.h"

void ABattleGM::GetUserInfo(const FString & ID, int PartyNum, int MaxPartyNum)
{
	PartySlotInfo.Emplace(ID);
	PartySlotInfo.Sort();

	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ABattlePC* PC = Cast<ABattlePC>(*Iter);
		if (PC)
		{
			PC->Client_PartyInfoSet(PartySlotInfo);
		}
	}
}
