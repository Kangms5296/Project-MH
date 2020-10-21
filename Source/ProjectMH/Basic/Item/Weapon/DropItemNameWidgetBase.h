// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropItemNameWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UDropItemNameWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	class UTextBlock* ItemName;
	class UBorder* ItemBg;

	void InitWidget();

	void SetName(FString NewName);
	void SetBgColor(FLinearColor NewColor);
};
