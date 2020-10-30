// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHUDBase.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UBattleHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP")));
	Stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("Stamina")));
	WeaponType = Cast<UImage>(GetWidgetFromName(TEXT("WeaponType")));
	WeaponCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponCount")));

	HideWeaponInfo();
}

void UBattleHUDBase::SetHP(float NewRatio)
{
	if (HP)
	{
		HP->SetPercent(NewRatio);
	}
}

void UBattleHUDBase::SetStamina(float NewRatio)
{
	if (Stamina)
	{
		Stamina->SetPercent(NewRatio);
	}
}

void UBattleHUDBase::SetCount(FString NewCount)
{
	if (WeaponCount)
	{
		WeaponCount->SetText(FText::FromString(NewCount));
	}
}

void UBattleHUDBase::ShowWeaponInfo()
{
	if (WeaponType)
	{
		WeaponType->SetVisibility(ESlateVisibility::Visible);
	}
	if (WeaponCount)
	{
		WeaponCount->SetVisibility(ESlateVisibility::Visible);
	}
}

void UBattleHUDBase::HideWeaponInfo()
{
	if (WeaponType)
	{
		WeaponType->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (WeaponCount)
	{
		WeaponCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}
