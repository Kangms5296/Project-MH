// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UBattleHUDBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class UScrollBox* T_InfoOutput;

	UPROPERTY()
	class UProgressBar* HP;

	void SetHP(float NewRatio);

	UPROPERTY()
	class UProgressBar* Stamina;

	void SetStamina(float NewRatio);

	UPROPERTY()
	class UImage* WeaponType;

	UPROPERTY()
	class UTextBlock* WeaponCount;

	void SetCount(FString NewCount);

	void ShowWeaponInfo();
	void HideWeaponInfo();

	void InitSlot();
	void PartySetting(const TArray<FString>& PartyArray);
};