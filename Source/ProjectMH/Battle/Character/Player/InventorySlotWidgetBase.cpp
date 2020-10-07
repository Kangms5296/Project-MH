// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidgetBase.h"
#include "MainWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "../../../Test/TestPC.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UInventorySlotWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	I_Background = Cast<UImage>(GetWidgetFromName(TEXT("Background")));
	I_ItemThumnail = Cast<UImage>(GetWidgetFromName(TEXT("ItemThumnail")));
	if (I_ItemThumnail)
	{
		I_ItemThumnail->SetVisibility(ESlateVisibility::Collapsed);
	}
	T_ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
}

void UInventorySlotWidgetBase::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	ATestPC* PC = Cast<ATestPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->ShowTooltip("", "");
	}
}

void UInventorySlotWidgetBase::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	UInventoryWidgetBase* Inventory = Cast<UInventoryWidgetBase>(OwnerWidget);
	if (Inventory)
	{
		UMainWidgetBase* MainWidget = Cast<UMainWidgetBase>(Inventory->OwnerWidget);
		if (MainWidget)
		{
			MainWidget->HideTooltip();
		}
	}
}

bool UInventorySlotWidgetBase::SlotSet(int NewIndex, int NewCount)
{
	IsUsing = true;
	ItemIndex = NewIndex;

	// Item Thumnail


	// Item Count Text
	ItemCount = NewCount;
	FString CountStr = FString::FromInt(ItemCount);
	T_ItemCount->SetText(FText::FromString(CountStr));

	return true;
}

bool UInventorySlotWidgetBase::SlotReset()
{
	IsUsing = false;

	ItemIndex = -1;

	ItemCount = 0;

	return true;
}

bool UInventorySlotWidgetBase::SlotAdd(int AddCount)
{
	ItemCount += AddCount;

	return true;
}

bool UInventorySlotWidgetBase::SlotSub(int SubCount)
{
	ItemCount -= SubCount;

	return true;
}

void UInventorySlotWidgetBase::SetOwnerWidget(UUserWidget * NewOwnerWidget)
{
	OwnerWidget = NewOwnerWidget;
}
