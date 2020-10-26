// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Item/ItemDataTable.h"
#include "InventorySlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UInventorySlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	class UBorder* I_UseEffect;
	class UBorder* I_ItemThumnail;
	class UTextBlock* T_ItemCount;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Slot")
	int RowIndex;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Slot")
	int ColIndex;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	bool IsUsing;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	FItemDataTable CurrentItem;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	int ItemCount;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Slot")
	TSubclassOf<class UInventorySlotWidgetBase> InventorySlotWidgetClass;

	bool SetSlot(FItemDataTable ItemData, int NewCount);
	bool ResetSlot();
	bool AddCount(int AddCount);
	bool SubCount(int SubCount);

	class UInventoryWidgetBase* InventoryWidget;
	void SetOwner(UInventoryWidgetBase * NewInventoryWidget);

	bool DoChangeThumnail;
	void DragSlotSet(FItemDataTable ItemData);

	void DoHighlightSlotBG();
	void UnDoHighlightSlotBG();
};
