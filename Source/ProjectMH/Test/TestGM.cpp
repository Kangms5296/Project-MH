// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGM.h"
#include "../Basic/Item/Weapon/DropItemBase.h"
#include "Kismet/GameplayStatics.h"

void ATestGM::BeginPlay()
{
	Super::BeginPlay();

	// 모든 유저의 BeginPlay 함수가 호출된 뒤, 레벨 내 모든 아이템을 화면에 표시
	FTimerHandle WaitHandle;
	float WaitTime = 3.0f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			TArray<AActor*> ItemList;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADropItemBase::StaticClass(), ItemList);

			for (int i = 0; i < ItemList.Num(); ++i)
			{
				ADropItemBase* TempItem = Cast<ADropItemBase>(ItemList[i]);

				TempItem->Init(GetItemData(FMath::RandRange(1, 3) * 10));
			}
		}), WaitTime, false);
}

FItemDataTable ATestGM::GetItemData(int Index) const
{
	return *ItemDataTable->FindRow<FItemDataTable>(*FString::FromInt(Index), TEXT("ItemIndex"));
}
