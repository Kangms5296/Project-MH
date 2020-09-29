// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPC.h"
#include "../Battle/Character/Player/InventoryWidgetBase.h"
#include "../Battle/Character/Player/InventorySlotWidgetBase.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
void ATestPC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		InventoryWidgetObject = CreateWidget<UInventoryWidgetBase>(this, InventoryWidgetClass);
		if (InventoryWidgetObject)
		{
			InventoryWidgetObject->AddToViewport();
			InventoryWidgetObject->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ATestPC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &ATestPC::ToggleInventory);
	InputComponent->BindAction(TEXT("GetItem1"), IE_Pressed, this, &ATestPC::GetItem1);
	InputComponent->BindAction(TEXT("GetItem2"), IE_Pressed, this, &ATestPC::GetItem2);
}

void ATestPC::ToggleInventory()
{
	if (IsShowInventory)
	{
		IsShowInventory = false;

		if (InventoryWidgetObject)
		{
			InventoryWidgetObject->SetVisibility(ESlateVisibility::Collapsed);
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}
	}
	else
	{
		IsShowInventory = true;

		if (InventoryWidgetObject)
		{
			InventoryWidgetObject->SetVisibility(ESlateVisibility::Visible);
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameOnly());
			/*
			FInputModeGameAndUI inputMode;
			inputMode.SetHideCursorDuringCapture(false);
			SetInputMode(inputMode);
			*/
		}
	}
}

void ATestPC::GetItem1()
{
	InventoryWidgetObject->AddItem(1, 2);
}

void ATestPC::GetItem2()
{
	InventoryWidgetObject->AddItem(2, 2);
}