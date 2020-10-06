// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetBase.h"
#include "InventorySlotWidgetBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../../../Test/MyDragDropOperation.h"

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
				CurSlot->SlotIndex = Row * Cols + Col;
				CurSlot->RowIndex = Row;
				CurSlot->ColIndex = Col;
				Slots.Add(CurSlot);

				// Slot ȭ�鿡 ǥ��.
				UUniformGridSlot* GridSlot = UGP_SlotManageGrid->AddChildToUniformGrid(CurSlot, Row, Col);
				GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

				// ���� ������ �Ľ�.
				// ..
			}
		}
	}

	T_Gold = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_Gold")));
	if (T_Gold)
	{
		// ���� ������ �Ľ�.
		FString Temp = "0";
		T_Gold->SetText(FText::FromString(Temp));
	}

	B_Header = Cast<UBorder>(GetWidgetFromName(TEXT("B_Header")));
	if (B_Header)
	{
	}
	
}

void UInventoryWidgetBase::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UInventoryWidgetBase::NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent, UDragDropOperation *& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Draging Start"));

	if (OutOperation == nullptr)
	{
		UMyDragDropOperation* oper = NewObject<UMyDragDropOperation>();
		OutOperation = oper;
		oper->DefaultDragVisual = this;
	}
}

bool UInventoryWidgetBase::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	return false;
}

FReply UInventoryWidgetBase::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}

	return reply.NativeReply;
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
				// ���� ���Կ� ���������� ������ ����ŭ �߰�
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
			// ���ο� ���Կ� ���������� ������ ����ŭ �߰�
			return true;
		}
	}

	// ���� ����, �� ���Կ� �߰��� �� ����
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
				// ���� ���Կ� ���������� ������ ����ŭ ����
				return true;
			}
		}
	}

	// ������ �������� ���� ���
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