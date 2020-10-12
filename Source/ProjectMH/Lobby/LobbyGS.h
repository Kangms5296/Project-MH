// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGS.generated.h"

/**
 *
 */
UCLASS()
class PROJECTMH_API ALobbyGS : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, ReplicatedUsing = "OnRep_PlayerCount", Category = "Network")
		int PlayerCount = 0;

	UFUNCTION()
		void OnRep_PlayerCount();

	UFUNCTION()
		void AddPlayer();

	void RemovePlayer();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
