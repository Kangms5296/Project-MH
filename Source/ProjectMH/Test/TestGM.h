// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Battle/Item/ItemDataTable.h"
#include "TestGM.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API ATestGM : public AGameModeBase
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
};
