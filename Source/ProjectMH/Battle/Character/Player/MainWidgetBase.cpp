// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "InventorySlotWidgetBase.h"
#include "MainWidgetDD.h"

void UMainWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryObject = Cast<UInventoryWidgetBase>(GetWidgetFromName(TEXT("InventoryWidget")));
	if (InventoryObject)
	{
		HideInventory();
	}
}

bool UMainWidgetBase::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : Drop"));
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
