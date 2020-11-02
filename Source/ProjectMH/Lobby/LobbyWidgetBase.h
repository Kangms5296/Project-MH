// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetBase.generated.h"

/**
 *
 */
UCLASS()
class PROJECTMH_API ULobbyWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UEditableTextBox* T_ChatInput;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UScrollBox* T_ChatOutput;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ProcessTextCommited(const FText& Text, ETextCommit::Type CommitMethod);

	void AddMessage(FText Message);
};
