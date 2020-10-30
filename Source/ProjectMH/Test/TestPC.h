// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Battle/Item/ItemDataTable.h"
#include "TestPC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API ATestPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATestPC();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UMainWidgetBase> MainWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UMainWidgetBase* MainWidgetObject;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UBattleHUDBase> BattleHUDClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UBattleHUDBase* BattleHUDObject;

	bool IsShowInventory;
	void ToggleInventory();

	bool IsShowTooltip;
	void ShowTooltip(FString ItemName, FString ItemDesc);
	void HideTooltip();
};
