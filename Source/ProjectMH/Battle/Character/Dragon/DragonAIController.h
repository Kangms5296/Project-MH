// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Dragon.h"
#include "DragonAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API ADragonAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADragonAIController();


	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UBlackboardComponent* BBComponent;

	void SetCurrentState(EDragonState NewState);

	void SetTarget(FVector NewLocation);

	void SetPlayer(AActor* Player);
};
