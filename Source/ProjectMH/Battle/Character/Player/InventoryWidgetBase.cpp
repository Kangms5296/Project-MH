// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetBase.h"
#include "InventorySlotWidgetBase.h"
#include "WidgetHeaderBase.h"
#include "MainWidgetDD.h"
#include "../../../MHGameInstance.h"
#include "../../../JsonHelper.h"
#include "Blueprint/WidgetTree.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventoryWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	// Slot 생성
	UGP_SlotManageGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UGP_SlotManageGrid")));
	if (UGP_SlotManageGrid)
	{
		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Col = 0; Col < Cols; ++Col)
			{
				// Slot 생성.
				UInventorySlotWidgetBase* CurSlot = CreateWidget<UInventorySlotWidgetBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InventorySlotWidgetClass);
				CurSlot->RowIndex = Row;
				CurSlot->ColIndex = Col;
				CurSlot->SetOwner(this);
				Slots.Add(CurSlot);

				// Slot 화면에 표시.
				UUniformGridSlot* GridSlot = UGP_SlotManageGrid->AddChildToUniformGrid(CurSlot, Row, Col);
				GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			}
		}
	}

	InventoryHeader = Cast<UWidgetHeaderBase>(GetWidgetFromName(TEXT("InventoryHeader")));
	{
		InventoryHeader->SetOwnerWidget(this);
	}

	T_Gold = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_Gold")));
	if (T_Gold)
	{
		// 저장 데이터 파싱.
		// CurrentMoney = 
		FString Temp = FString::FromInt(CurrentMoney);
		T_Gold->SetText(FText::FromString(Temp));
	}
}

bool UInventoryWidgetBase::AddItem(FItemDataTable ItemData, int Count)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if ((Slots[i]->IsUsing)	&& (Slots[i]->CurrentItem.ItemIndex == ItemData.ItemIndex))
		{
			if (Slots[i]->ItemCount + Count <= ItemData.Value2)
			{
				bool Result = Slots[i]->AddCount(Count);
				if (Result)
				{
					// 기존 슬롯에 성공적으로 아이템 수만큼 추가
					return true;
				}
			}
			else
			{
				Slots[i]->AddCount(ItemData.Value2 - Slots[i]->ItemCount);
				Count -= ItemData.Value2 - Slots[i]->ItemCount;
			}
		}
	}

	int EmptyRow;
	int EmptyCol;
	if (GetEmptySlotIndex(EmptyRow, EmptyCol))
	{
		bool Result = SetSlot(EmptyRow, EmptyCol, ItemData, Count);
		if (Result)
		{
			// 새로운 슬롯에 성공적으로 아이템 수만큼 추가
			return true;
		}
	}

	// 기존 슬롯, 새 슬롯에 추가할 수 없음
	return false;
}

bool UInventoryWidgetBase::SubItem(FItemDataTable ItemData, int Count)
{
	// 현재 가지고 있는 아이템 중 ItemData의 ItemIndex에 해당하는 아이템이 있는지 확인
	for (int i = 0; i < Slots.Num(); i++)
		if (Slots[i]->IsUsing && Slots[i]->CurrentItem.ItemIndex == ItemData.ItemIndex)
			// 있으면 SubCount 실행
			return Slots[i]->SubCount(Count);

	// 기존에 아이템이 없는 경우
	return false;
}

bool UInventoryWidgetBase::AddItemAtSlot(int Row, int Col, int Count)
{
	bool Result = Slots[GetSlotIndex(Row, Col)]->AddCount(Count);

	return Result;
}

bool UInventoryWidgetBase::SubItemAtSlot(int Row, int Col, int Count)
{
	bool Result = Slots[GetSlotIndex(Row, Col)]->SubCount(Count);

	return Result;
}

void UInventoryWidgetBase::ClearInventory()
{
	for (UInventorySlotWidgetBase* MySlot : Slots)
	{
		MySlot->ResetSlot();
	}
}

bool UInventoryWidgetBase::SetSlot(int Row, int Col, FItemDataTable ItemData, int Count)
{
	bool Result = Slots[GetSlotIndex(Row, Col)]->SetSlot(ItemData, Count);

	return Result;
}

void UInventoryWidgetBase::ResetSlot(int Row, int Col)
{
	Slots[GetSlotIndex(Row, Col)]->ResetSlot();
}

bool UInventoryWidgetBase::GetEmptySlotIndex(int& EmptyRow, int& EmptyCol)
{
	for (UInventorySlotWidgetBase* MySlot : Slots)
	{
		if (false == MySlot->IsUsing)
		{
			EmptyRow = MySlot->RowIndex;
			EmptyCol = MySlot->ColIndex;
			return true;
		}
	}

	return false;
}

int UInventoryWidgetBase::GetSlotIndex(int Row, int Col)
{
	return Row * Cols + Col;
}

void UInventoryWidgetBase::AddMoney(int Count)
{
	if (T_Gold)
	{
		CurrentMoney += Count;

		FString Temp = FString::FromInt(CurrentMoney);
		T_Gold->SetText(FText::FromString(Temp));
	}
}

void UInventoryWidgetBase::SubMoney(int Count)
{
	if (T_Gold)
	{
		CurrentMoney += Count;
		CurrentMoney = CurrentMoney < 0 ? 0 : CurrentMoney;

		FString Temp = FString::FromInt(CurrentMoney);
		T_Gold->SetText(FText::FromString(Temp));
	}
}

bool UInventoryWidgetBase::AddCount(int Index, int Count)
{
	// 현재 가지고 있는 아이템 중 ItemData의 ItemIndex에 해당하는 아이템이 있는지 확인
	for (int i = 0; i < Slots.Num(); i++)
		if (Slots[i]->IsUsing && Slots[i]->CurrentItem.ItemIndex == Index)
			// 있으면 SubCount 실행
			return Slots[i]->AddCount(Count);

	// 기존에 아이템이 없는 경우
	return false;
}

bool UInventoryWidgetBase::SubCount(int Index, int Count)
{
	// 현재 가지고 있는 아이템 중 ItemData의 ItemIndex에 해당하는 아이템이 있는지 확인
	for (int i = 0; i < Slots.Num(); i++)
		if (Slots[i]->IsUsing && Slots[i]->CurrentItem.ItemIndex == Index)
			// 있으면 SubCount 실행
			return Slots[i]->SubCount(Count);

	// 기존에 아이템이 없는 경우
	return false;
}
