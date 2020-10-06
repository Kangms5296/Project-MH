// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
private:
	const int MaxColumnCount = 10;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	class UUniformGridPanel* UGP_SlotManageGrid;
	class UTextBlock* T_Gold;
	class UBorder* B_Header;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Slot")
	TSubclassOf<class UInventorySlotWidgetBase> InventorySlotWidgetClass;
	TArray <class UInventorySlotWidgetBase*> Slots;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Slot")
	int Rows;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Slot")
	int Cols;

	bool AddItem(int ItemIndex, int Count); // 인벤토리 내 Index에 해당하는 아이템을 Count 만큼 추가. 만약, 기존에 없는 아이템이면 새로운 Slot에 아이템을 추가.
	bool SubItem(int ItemIndex, int Count); // 인벤토리 내 Index에 해당하는 아이템을 Count 만큼 제거. 만약, 기존에 없는 아이템이면 False 반환.

	bool AddItemAtSlot(int SlotIndex, int Count); // RowIndex, ColIndex 위치의 아이템 Count 만큼 추가.
	bool SubItemAtSlot(int SlotIndex, int Count); // RowIndex, ColIndex 위치의 아이템 Count 만큼 제거.

	void ClearInventory();

	bool SetSlot(int SlotIndex, int ItemIndex, int Count);
	void ResetSlot(int SlotIndex);

	int GetEmptySlotIndex(); // 인벤토리 내 미사용 Slot Index 반환

	bool IsHeaderPressed;
	FVector2D DragStartPos;
	FVector2D InventoryPos;
};
