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

	bool AddItem(int ItemIndex, int Count); // �κ��丮 �� Index�� �ش��ϴ� �������� Count ��ŭ �߰�. ����, ������ ���� �������̸� ���ο� Slot�� �������� �߰�.
	bool SubItem(int ItemIndex, int Count); // �κ��丮 �� Index�� �ش��ϴ� �������� Count ��ŭ ����. ����, ������ ���� �������̸� False ��ȯ.

	bool AddItemAtSlot(int SlotIndex, int Count); // RowIndex, ColIndex ��ġ�� ������ Count ��ŭ �߰�.
	bool SubItemAtSlot(int SlotIndex, int Count); // RowIndex, ColIndex ��ġ�� ������ Count ��ŭ ����.

	void ClearInventory();

	bool SetSlot(int SlotIndex, int ItemIndex, int Count);
	void ResetSlot(int SlotIndex);

	int GetEmptySlotIndex(); // �κ��丮 �� �̻�� Slot Index ��ȯ

	bool IsHeaderPressed;
	FVector2D DragStartPos;
	FVector2D InventoryPos;
};
