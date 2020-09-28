// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetBase.h"
#include "InventorySlotWidgetBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UInventoryWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetTree)
	{
		TArray<UWidget*> Widgets;
		WidgetTree->GetAllWidgets(Widgets);

		int Index = 0;
		for (UWidget* Widget : Widgets)
		{
			if (Widget && Widget->IsA(UInventorySlotWidgetBase::StaticClass()))
			{
				if (UInventorySlotWidgetBase* InventorySlot = Cast<UInventorySlotWidgetBase>(Widget))
				{
					InventorySlot->SlotIndex = Index;
					InventorySlot->RowIndex = Index / MaxColumnCount;
					InventorySlot->ColIndex = Index % MaxColumnCount;
					++Index;

					Slots.Add(InventorySlot);
				}
			}
		}
	}
}

bool UInventoryWidgetBase::AddItem(int ItemIndex, int Count)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i]->IsUsing && Slots[i]->ItemIndex == ItemIndex)
		{
			bool Result = Slots[i]->SlotAdd(Count);
			if (Result)
			{
				// 기존 슬롯에 성공적으로 아이템 수만큼 추가
				return true;
			}
		}
	}

	int SlotIndex = GetEmptySlotIndex();
	if (SlotIndex != -1)
	{
		bool Result = AddItemAtSlot(SlotIndex, Count);
		if (Result)
		{
			// 새로운 슬롯에 성공적으로 아이템 수만큼 추가
			return true;
		}
	}

	// 기존 슬롯, 새 슬롯에 추가할 수 없음
	return false;
}

bool UInventoryWidgetBase::SubItem(int ItemIndex, int Count)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i]->IsUsing && Slots[i]->ItemIndex == ItemIndex)
		{
			bool Result = Slots[i]->SlotSub(Count);
			if (Result)
			{
				// 기존 슬롯에 성공적으로 아이템 수만큼 제거
				return true;
			}
		}
	}

	// 기존에 아이템이 없는 경우
	return false;
}

bool UInventoryWidgetBase::AddItemAtSlot(int SlotIndex, int Count)
{
	bool Result = Slots[SlotIndex]->SlotAdd(Count);
	
	return Result;
}

bool UInventoryWidgetBase::SubItemAtSlot(int SlotIndex, int Count)
{
	bool Result = Slots[SlotIndex]->SlotSub(Count);

	return Result;
}

void UInventoryWidgetBase::ClearInventory()
{
	for (UInventorySlotWidgetBase* MySlot : Slots)
	{
		MySlot->SlotReset();
	}
}

bool UInventoryWidgetBase::SetSlot(int SlotIndex, int ItemIndex, int Count)
{
	bool Result = Slots[SlotIndex]->SlotSet(ItemIndex, Count);

	return Result;
}

void UInventoryWidgetBase::ResetSlot(int SlotIndex)
{
	Slots[SlotIndex]->SlotReset();
}

int UInventoryWidgetBase::GetEmptySlotIndex()
{
	for (UInventorySlotWidgetBase* MySlot : Slots)
	{
		if (false == MySlot->IsUsing)
		{
			return MySlot->SlotIndex;
		}
	}

	return -1;
}
