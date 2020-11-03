// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGM.h"
#include "BattlePC.h"
#include "../Basic/Item/Weapon/DropItemBase.h"
#include "Kismet/GameplayStatics.h"

void ABattleGM::BeginPlay()
{
	Super::BeginPlay();

	// ��� ������ BeginPlay �Լ��� ȣ��� ��, ���� �� ��� �������� ȭ�鿡 ǥ��

	FTimerHandle WaitHandle;
	float WaitTime = 3.0f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			TArray<AActor*> ItemList;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADropItemBase::StaticClass(), ItemList);

			for (int i = 0; i < ItemList.Num(); ++i)
			{
				ADropItemBase* TempItem = Cast<ADropItemBase>(ItemList[i]);

				TempItem->Init(GetItemData(FMath::RandRange(1, 7) * 10));
			}
		}), WaitTime, false);

}

FItemDataTable ABattleGM::GetItemData(int Index) const
{
	return *ItemDataTable->FindRow<FItemDataTable>(*FString::FromInt(Index), TEXT("ItemIndex"));
	
//	return FItemDataTable();
}

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
