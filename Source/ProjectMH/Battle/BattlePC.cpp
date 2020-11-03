// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePC.h"
#include "Kismet/GameplayStatics.h"
#include "../MHGameInstance.h"
#include "BattleGM.h"

#include "Character/Player/InventoryWidgetBase.h"
#include "Character/Player/InventorySlotWidgetBase.h"
#include "Character/Player/MainWidgetBase.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Engine/GameViewportClient.h"
#include "Character/Player/PlayerCameraManagerBase.h"
#include "UI/BattleHUDBase.h"

ABattlePC::ABattlePC()
{
	PlayerCameraManagerClass = APlayerCameraManagerBase::StaticClass();
}

void ABattlePC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		MainWidgetObject = CreateWidget<UMainWidgetBase>(this, MainWidgetClass);
		if (MainWidgetObject)
		{
			MainWidgetObject->AddToViewport();
		}

		BattleHUDObject = CreateWidget<UBattleHUDBase>(this, BattleHUDClass);
		if (BattleHUDClass)
		{
			BattleHUDObject->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());

			UMHGameInstance* GI = Cast<UMHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			Server_PartyInfo(GI->GetUserID(), GI->GetPartyNum(), GI->GetMaxPartyNum());
		}
	}
}

void ABattlePC::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &ABattlePC::ToggleInventory);
	InputComponent->BindAction(TEXT("TestDamage"), IE_Released, this, &ABattlePC::TestDamage);
}

void ABattlePC::Server_PartyInfo_Implementation(const FString & PartyID, int PartyNum, int MaxPartyNum)
{
	ABattleGM* GM = Cast<ABattleGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->GetUserInfo(PartyID, PartyNum, MaxPartyNum);
	}
}

void ABattlePC::Client_PartyInfoSet_Implementation(const TArray<FString>& PartySlotsID)
{
	if (IsLocalPlayerController() && BattleHUDObject)
	{
		BattleHUDObject->PartySetting(PartySlotsID);
	}
}

void ABattlePC::ToggleInventory()
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

void ABattlePC::ShowTooltip(FString ItemName, FString ItemDesc)
{
	if (IsShowTooltip)
		return;

	if (MainWidgetObject)
	{
		FVector2D MousePos;
		GetMousePosition(MousePos.X, MousePos.Y);

		FIntPoint ViewportSize;
		GetViewportSize(ViewportSize.X, ViewportSize.Y);

		MainWidgetObject->ShowTooltip(ItemName, ItemDesc, MousePos, ViewportSize);

		IsShowTooltip = true;
	}
}

void ABattlePC::HideTooltip()
{
	if (!IsShowTooltip)
		return;

	if (MainWidgetObject)
	{
		MainWidgetObject->HideTooltip();

		IsShowTooltip = false;
	}
}

void ABattlePC::TestDamage()
{

}
