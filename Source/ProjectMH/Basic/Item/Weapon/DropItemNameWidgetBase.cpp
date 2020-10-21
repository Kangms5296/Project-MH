// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItemNameWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UDropItemNameWidgetBase::InitWidget()
{
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));

	ItemBg = Cast<UBorder>(GetWidgetFromName(TEXT("Background")));
}

void UDropItemNameWidgetBase::SetName(FString NewName)
{
	if (ItemName)
	{
		ItemName->SetText(FText::FromString(NewName));
	}
}

void UDropItemNameWidgetBase::SetBgColor(FLinearColor NewColor)
{
	if (ItemBg)
	{
		ItemBg->SetBrushColor(NewColor);
	}
}
