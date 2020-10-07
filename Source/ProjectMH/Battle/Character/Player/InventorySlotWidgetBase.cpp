// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidgetBase.h"
#include "MainWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "../../../Test/TestPC.h"
#include "SlotWidgetDD.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventorySlotWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	I_Background = Cast<UBorder>(GetWidgetFromName(TEXT("Background")));

	I_ItemThumnail = Cast<UBorder>(GetWidgetFromName(TEXT("ItemThumnail")));
	if (I_ItemThumnail)
	{
		I_ItemThumnail->SetVisibility(ESlateVisibility::Collapsed);
		I_ItemThumnail->Visibility = ESlateVisibility::Visible;
	}

	T_ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	if (T_ItemCount)
	{
		T_ItemCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventorySlotWidgetBase::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	ATestPC* PC = Cast<ATestPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && IsUsing)
	{
		PC->ShowTooltip(CurrentItem.ItemName, CurrentItem.ItemDescription);
	}
}

void UInventorySlotWidgetBase::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
	{
		// Nothinng To do
	}
	else
	{
		ATestPC* PC = Cast<ATestPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PC && IsUsing)
		{
			PC->HideTooltip();
		}
	}
}

FReply UInventorySlotWidgetBase::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// ��Ŭ��
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
	{
		if (IsUsing)
		{
			// ������ ���
			SlotSub(1);
		}
	}
	// ��Ŭ�� �巡��&���
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		if (IsUsing)
		{
			// Slot Swap
			Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		}
	}

	return Reply.NativeReply;
}

void UInventorySlotWidgetBase::NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent, UDragDropOperation *& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	USlotWidgetDD* SlotDD = Cast<USlotWidgetDD>(UWidgetBlueprintLibrary::CreateDragDropOperation(USlotWidgetDD::StaticClass()));
	if (SlotDD == nullptr)
	{
		return;
	}

	SlotDD->BaseSlot = this;

	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UInventorySlotWidgetBase* DragedSlot = CreateWidget<UInventorySlotWidgetBase>(PC, InventorySlotWidgetClass);
	DragedSlot->AddToViewport();
	DragedSlot->SlotSet(CurrentItem, ItemCount);

	SlotDD->DefaultDragVisual = DragedSlot;
	SlotDD->Pivot = EDragPivot::MouseDown;

	OutOperation = SlotDD;
}

bool UInventorySlotWidgetBase::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{

	return false;
}

bool UInventorySlotWidgetBase::SlotSet(FItemDataTable ItemData, int NewCount)
{
	CurrentItem = ItemData;

	// Item Thumnail
	if (I_ItemThumnail)
	{
		FStreamableManager Loader;
		I_ItemThumnail->SetBrushFromTexture(Loader.LoadSynchronous<UTexture2D>(CurrentItem.ItemThumnail));
		I_ItemThumnail->SetVisibility(ESlateVisibility::Visible);
	}

	// Item Count Text
	if (T_ItemCount)
	{
		ItemCount = NewCount;
		FString CountStr = FString::FromInt(ItemCount);
		T_ItemCount->SetText(FText::FromString(CountStr));
		T_ItemCount->SetVisibility(ESlateVisibility::Visible);
	}
	IsUsing = true;

	return true;
}
bool UInventorySlotWidgetBase::SlotReset()
{
	IsUsing = false;

	if (I_ItemThumnail)
	{
		I_ItemThumnail->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (T_ItemCount)
	{
		T_ItemCount->SetVisibility(ESlateVisibility::Collapsed);
	}

	return true;
}

bool UInventorySlotWidgetBase::SlotAdd(int AddCount)
{
	ItemCount += AddCount;
	FString CountStr = FString::FromInt(ItemCount);
	T_ItemCount->SetText(FText::FromString(CountStr));

	return true;
}

bool UInventorySlotWidgetBase::SlotSub(int SubCount)
{
	ItemCount -= SubCount;
	if (ItemCount <= 0)
	{
		SlotReset();

		ATestPC* PC = Cast<ATestPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PC)
		{
			PC->HideTooltip();
		}
	}
	else
	{
		FString CountStr = FString::FromInt(ItemCount);
		T_ItemCount->SetText(FText::FromString(CountStr));
	}

	return true;
}