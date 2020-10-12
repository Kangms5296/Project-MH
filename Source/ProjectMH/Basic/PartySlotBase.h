// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartySlotBase.generated.h"

/**
 *
 */
UCLASS()
class PROJECTMH_API UPartySlotBase : public UUserWidget
{
	GENERATED_BODY()
public:
	//	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	//	class UBorder* I_ClassIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UTextBlock* T_UserNN;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UTextBlock* T_UserID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UButton* B_Player;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetUserInfo();

	bool bUse = false;
};
