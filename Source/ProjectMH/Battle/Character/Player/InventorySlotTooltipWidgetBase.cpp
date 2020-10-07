// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotTooltipWidgetBase.h"
#include "Components/TextBlock.h"

void UInventorySlotTooltipWidgetBase::NativeConstruct()
{
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemDesc = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDesc")));
}

void UInventorySlotTooltipWidgetBase::SetTooltipInfo(FString NewName, FString NewDesc)
{
	this->ItemName->SetText(FText::FromString(NewName));
	this->ItemDesc->SetText(FText::FromString(NewDesc));
}

void UInventorySlotTooltipWidgetBase::SetTooltipPos(FVector2D NewPos)
{
	SetPositionInViewport(NewPos);
}

void UInventorySlotTooltipWidgetBase::SetTooltipOffset(FVector2D OffsetPos)
{
	SetAlignmentInViewport(OffsetPos);
}
