// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyWidgetBase.generated.h"

/**
 *
 */
UCLASS()
class PROJECTMH_API UPartyWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* B_Start;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* B_Ready;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UScrollBox* T_PartyOutput;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* ConnectCount;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void PressStartButton();

	UFUNCTION()
	void PressReadyButton();

	void HideStartGameButton();
	void ShowStartGameButton();

	void InitSlot();

	void Party(const TArray<FString>& PartyArray);

	void Ready(const FString& ID);

};
