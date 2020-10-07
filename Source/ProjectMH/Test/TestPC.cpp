// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPC.h"
#include "../Battle/Character/Player/InventoryWidgetBase.h"
#include "../Battle/Character/Player/InventorySlotWidgetBase.h"
#include "../Battle/Character/Player/MainWidgetBase.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
void ATestPC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		MainWidgetObject = CreateWidget<UMainWidgetBase>(this, MainWidgetClass);
		if (MainWidgetObject)
		{
			MainWidgetObject->AddToViewport();
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
		if (MainWidgetObject)
		{
			IsShowInventory = false;

			MainWidgetObject->HideInventory();
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}
	}
	else
	{
		if (MainWidgetObject)
		{
			IsShowInventory = true;

			MainWidgetObject->ShowInventory();
			bShowMouseCursor = true;

			FInputModeGameAndUI InputMode;
			InputMode.SetHideCursorDuringCapture(false);
			SetInputMode(InputMode);


			int ViewportX;
			int ViewportY;
			GetViewportSize(ViewportX, ViewportY);
			SetMouseLocation(ViewportX * 0.5f, ViewportY * 0.5f);
		}
	}
}

void ATestPC::GetItem1()
{
	FItemDataTable Temp = *ItemDataTable->FindRow<FItemDataTable>("10", TEXT("ItemIndex"));
	MainWidgetObject->InventoryObject->AddItem(Temp, 1);
}

void ATestPC::GetItem2()
{
	FItemDataTable Temp = *ItemDataTable->FindRow<FItemDataTable>("20", TEXT("ItemIndex"));
	MainWidgetObject->InventoryObject->AddItem(Temp, 2);
}

void ATestPC::ShowTooltip(FString ItemName, FString ItemDesc)
{
	if (IsShowTooltip)
		return;

	if (MainWidgetObject)
	{
		FVector2D MousePos;
		GetMousePosition(MousePos.X, MousePos.Y);

		FIntPoint ViewportSiz;
		GetViewportSize(ViewportSiz.X, ViewportSiz.Y);

		MainWidgetObject->ShowTooltip(ItemName, ItemDesc, MousePos, ViewportSiz);

		IsShowTooltip = true;
	}
}

void ATestPC::HideTooltip()
{
	if (!IsShowTooltip)
		return;

	if (MainWidgetObject)
	{
		MainWidgetObject->HideTooltip();

		IsShowTooltip = false;
	}
}
