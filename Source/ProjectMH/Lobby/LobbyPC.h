// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

/**
 *
 */
UCLASS()
class PROJECTMH_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	//채팅창
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class ULobbyWidgetBase> LobbyWidgetClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UI")
	class ULobbyWidgetBase* LobbyWidgetObject;

	//파티창
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UPartyWidgetBase> PartyWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UPartyWidgetBase* PartyWidgetObject;

	UFUNCTION(Server, Reliable)
	void C2S_SendMessage(const FText& Message);
	void C2S_SendMessage_Implementation(const FText& Message);

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(const FText& Message);
	void S2C_SendMessage_Implementation(const FText& Message);

	virtual void SetupInputComponent() override;

	void ToggleParty();
	void ShowParty();
	void HideParty();

	void ShowStart();
	void HideStart();

	
	UFUNCTION(Server, Reliable)
	void Server_Party(const FString& PartyID);
	void Server_Party_Implementation(const FString& PartyID);

	UFUNCTION(Client, Reliable)
	void Client_PartySet(const TArray<FString>& PartySlotsID);
	void Client_PartySet_Implementation(const TArray<FString>& PartySlotsID);

	UFUNCTION(Server, Reliable)
	void Server_Ready(const FString& UserID);
	void Server_Ready_Implementation(const FString& UserID);

	UFUNCTION(Client, Reliable)
	void Client_ReadySet(const FString& UserSetID);
	void Client_ReadySet_Implementation(const FString& UserSetID);
	
};
