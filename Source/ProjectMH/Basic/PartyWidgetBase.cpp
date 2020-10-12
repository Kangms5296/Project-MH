// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyWidgetBase.h"
#include "Components/ScrollBox.h"		//PartyOutput
#include "Components/Button.h"			//start,Ready Button
#include "Components/ScrollBox.h"		//PartyOutput
#include "PartySlotBase.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "../MHGameInstance.h"

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

	ConnectCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ConnectCount")));
}

void UPartyWidgetBase::PressStartButton()
{

}

void UPartyWidgetBase::PressReadyButton()
{

}

void UPartyWidgetBase::SetPlayerCount(int NewPlayerCount)
{


	FString Temp = FString::Printf(TEXT("%d"), NewPlayerCount);
	if (ConnectCount)
	{
		ConnectCount->SetText(FText::FromString(Temp));
	}


}
/*
for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Col = 0; Col < Cols; ++Col)
			{
				// Slot 생성.
				UInventorySlotWidgetBase* CurSlot = CreateWidget<UInventorySlotWidgetBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InventorySlotWidgetClass);
				CurSlot->SlotIndex = Row * Cols + Col;
				CurSlot->RowIndex = Row;
				CurSlot->ColIndex = Col;
				CurSlot->SetOwnerWidget(this);
				Slots.Add(CurSlot);

				// Slot 화면에 표시.
				UUniformGridSlot* GridSlot = UGP_SlotManageGrid->AddChildToUniformGrid(CurSlot, Row, Col);
				GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

				// 저장 데이터 파싱.
				// ..
			}
		}

*/
void UPartyWidgetBase::AddSlots(int PlayerCount)
{
	/*
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(T_ChatOutput);
	class UPartyWidgetBase* PartyWidgetObject;

	TSubclassOf<class UPartySlotBase> PartySlotClass;
	*/
	if (T_PartyOutput)
	{
		UPartySlotBase* NewPartySlot = CreateWidget<UPartySlotBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PartySlotClass);

		NewPartySlot->SetUserInfo();
		//		UPartySlotBase* NewPartySlot = NewObject<UPartySlotBase>(T_PartyOutput);
		//		if (NewPartySlot)
		{
			PartySlots.Add(NewPartySlot);
			//NewPartySlot->SetUserInfo();
//			T_PartyOutput->AddChild(NewPartySlot);
			for (int i = 0; i < PartySlots.Num(); i++)
			{
				T_PartyOutput->AddChild(PartySlots[i]);
			}
			T_PartyOutput->ScrollToEnd();
			UE_LOG(LogClass, Warning, TEXT("Add Player End"));
		}
	}
}

void UPartyWidgetBase::SubSlots(int PlayerCount)
{

}

