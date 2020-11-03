// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Item/ItemDataTable.h"
#include "BattleGM.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API ABattleGM : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
	TSubclassOf<class ADropItemBase> DropItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UDataTable* ItemDataTable;

	UFUNCTION(BlueprintCallable)
	FItemDataTable GetItemData(int Index) const;

	TArray <FString> PartySlotInfo;
	TArray <int> PartySequence;

	void GetUserInfo(const FString& ID, int PartyNum, int MaxPartyNum);
};
