// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestPC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API ATestPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UMainWidgetBase> MainWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UMainWidgetBase* MainWidgetObject;

	bool IsShowInventory;
	void ToggleInventory();

	void GetItem1();
	void GetItem2();
};
