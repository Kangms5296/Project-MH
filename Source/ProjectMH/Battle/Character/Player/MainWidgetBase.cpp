// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "InventorySlotWidgetBase.h"
#include "InventorySlotTooltipWidgetBase.h"
#include "MainWidgetDD.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMainWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryObject = Cast<UInventoryWidgetBase>(GetWidgetFromName(TEXT("InventoryWidget")));
	if (InventoryObject)
	{
		HideInventory();
	}

	InventoryTooltipObject = Cast<UInventorySlotTooltipWidgetBase>(GetWidgetFromName(TEXT("InventoryTooltipWidget")));
	if (InventoryTooltipObject)
	{
		HideTooltip();
	}

	Crosshair = Cast<UImage>(GetWidgetFromName(TEXT("Crosshair")));
	if (Crosshair)
	{
		HideCrosshair();
	}

	BulletText = Cast<UTextBlock>(GetWidgetFromName(TEXT("BulletText")));
	if (BulletText)
	{
		HideBulletText();
	}
}

bool UMainWidgetBase::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UMainWidgetDD* WidgetDD = Cast<UMainWidgetDD>(InOperation);
	if (WidgetDD == nullptr)
	{
		return false;
	}

	WidgetDD->WidgetToDrag->AddToViewport();
	FVector2D NewPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition()) - WidgetDD->MouseOffset;
	WidgetDD->WidgetToDrag->SetPositionInViewport(NewPosition, false);

	return true;
}

void UMainWidgetBase::ShowInventory()
{
	if (InventoryObject)
	{
		InventoryObject->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidgetBase::HideInventory()
{
	if (InventoryObject)
	{
		InventoryObject->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainWidgetBase::ShowTooltip(FString NewItemName, FString NewItemDesc, FVector2D MousePos, FIntPoint ViewportSize)
{
	if (InventoryTooltipObject)
	{
		InventoryTooltipObject->SetTooltipInfo(NewItemName, NewItemDesc);

		FVector2D OffsetPos;
		OffsetPos.X = MousePos.X / ViewportSize.X;
		OffsetPos.Y = MousePos.Y / ViewportSize.Y;
		InventoryTooltipObject->SetTooltipOffset(OffsetPos);

		InventoryTooltipObject->SetTooltipPos(MousePos);

		InventoryTooltipObject->AddToViewport();
	}
}

void UMainWidgetBase::HideTooltip()
{
	if (InventoryTooltipObject)
	{
		InventoryTooltipObject->RemoveFromViewport();
	}
}

void UMainWidgetBase::ShowCrosshair()
{
	if (Crosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidgetBase::HideCrosshair()
{
	if (Crosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainWidgetBase::SetBulletText(FString NewText)
{
	if (BulletText)
	{
		BulletText->SetText(FText::FromString(NewText));
	}
}

void UMainWidgetBase::ShowBulletText()
{
	if (BulletText)
	{
		BulletText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidgetBase::HideBulletText()
{
	if (BulletText)
	{
		BulletText->SetVisibility(ESlateVisibility::Collapsed);
	}
}
