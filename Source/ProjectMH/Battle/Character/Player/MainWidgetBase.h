// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UMainWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY()
	class UInventoryWidgetBase* InventoryObject;

	void ShowInventory();
	void HideInventory();

	UPROPERTY()
	class UInventorySlotTooltipWidgetBase* InventoryTooltipObject;

	void ShowTooltip(FString NewItemName, FString NewItemDesc, FVector2D MousePos, FIntPoint ViewportSize);
	void HideTooltip();

	UPROPERTY()
	class UImage* Crosshair;

	void ShowCrosshair();
	void HideCrosshair();

	UPROPERTY()
	class UTextBlock* BulletText;

	void SetBulletText(FString NewText);
	void ShowBulletText();
	void HideBulletText();
};
