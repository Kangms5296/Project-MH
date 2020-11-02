// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePC.h"
#include "UI/BattleHUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "../MHGameInstance.h"
#include "BattleGM.h"


void ABattlePC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (BattleHUDClass)
		{
			{
				BattleHUDObject = CreateWidget<UBattleHUDBase>(this, BattleHUDClass);
				BattleHUDObject->AddToViewport();

				bShowMouseCursor = true;
				SetInputMode(FInputModeGameAndUI());

				UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
				Server_PartyInfo(GI->GetUserID(), GI->GetPartyNum(), GI->GetMaxPartyNum());
			}
		}
	}

}

void ABattlePC::Server_PartyInfo_Implementation(const FString & PartyID, int PartyNum, int MaxPartyNum)
{
	ABattleGM* GM = Cast<ABattleGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->GetUserInfo(PartyID, PartyNum, MaxPartyNum);
	}
}

void ABattlePC::Client_PartyInfoSet_Implementation(const TArray<FString>& PartySlotsID)
{
	if (IsLocalPlayerController() && BattleHUDObject)
	{
		BattleHUDObject->PartySetting(PartySlotsID);
	}
}