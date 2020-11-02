// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattlePC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API ABattlePC : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UBattleHUDBase> BattleHUDClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UI")
	class UBattleHUDBase* BattleHUDObject;

	UFUNCTION(Server, Reliable)
	void Server_PartyInfo(const FString& PartyID, int PartyNum, int MaxPartyNum);
	void Server_PartyInfo_Implementation(const FString& PartyID, int PartyNum, int MaxPartyNum);

	UFUNCTION(Client, Reliable)
	void Client_PartyInfoSet(const TArray<FString>& PartySlotsID);
	void Client_PartyInfoSet_Implementation(const TArray<FString>& PartySlotsID);
};
