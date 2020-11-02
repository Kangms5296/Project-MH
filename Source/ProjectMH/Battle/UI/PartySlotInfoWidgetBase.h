// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartySlotInfoWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UPartySlotInfoWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UTextBlock* T_UserInfoID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UProgressBar* P_UserInfoHP;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetUserInfoID(FString GetUserID);
	void SetUserInfoHP(float GetUserHP);

	bool bUse = false;
	int Num = 0;
};
