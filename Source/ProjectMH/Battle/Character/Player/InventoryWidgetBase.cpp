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

	// Slot ����
	UGP_SlotManageGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UGP_SlotManageGrid")));
	if (UGP_SlotManageGrid)
	{
		for (int Row = 0; Row < Rows; ++Row)
		{
			for (int Col = 0; Col < Cols; ++Col)
			{
				// Slot ����.
				UInventorySlotWidgetBase* CurSlot = CreateWidget<UInventorySlotWidgetBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InventorySlotWidgetClass);
				CurSlot->RowIndex = Row;
				CurSlot->ColIndex = Col;
				CurSlot->SetOwner(this);
				Slots.Add(CurSlot);

				// Slot ȭ�鿡 ǥ��.
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
		// ���� ������ �Ľ�.
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
					// ���� ���Կ� ���������� ������ ����ŭ �߰�
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
			// ���ο� ���Կ� ���������� ������ ����ŭ �߰�
			return true;
		}
	}

	// ���� ����, �� ���Կ� �߰��� �� ����
	return false;
}

bool UInventoryWidgetBase::SubItem(FItemDataTable ItemData, int Count)
{
	// ���� ������ �ִ� ������ �� ItemData�� ItemIndex�� �ش��ϴ� �������� �ִ��� Ȯ��
	for (int i = 0; i < Slots.Num(); i++)
		if (Slots[i]->IsUsing && Slots[i]->CurrentItem.ItemIndex == ItemData.ItemIndex)
			// ������ SubCount ����
			return Slots[i]->SubCount(Count);

	// ������ �������� ���� ���
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
	// ���� ������ �ִ� ������ �� ItemData�� ItemIndex�� �ش��ϴ� �������� �ִ��� Ȯ��
	for (int i = 0; i < Slots.Num(); i++)
		if (Slots[i]->IsUsing && Slots[i]->CurrentItem.ItemIndex == Index)
			// ������ SubCount ����
			return Slots[i]->AddCount(Count);

	// ������ �������� ���� ���
	return false;
}

bool UInventoryWidgetBase::SubCount(int Index, int Count)
{
	// ���� ������ �ִ� ������ �� ItemData�� ItemIndex�� �ش��ϴ� �������� �ִ��� Ȯ��
	for (int i = 0; i < Slots.Num(); i++)
		if (Slots[i]->IsUsing && Slots[i]->CurrentItem.ItemIndex == Index)
			// ������ SubCount ����
			return Slots[i]->SubCount(Count);

	// ������ �������� ���� ���
	return false;
}
