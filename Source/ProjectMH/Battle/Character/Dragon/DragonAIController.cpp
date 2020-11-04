// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Dragon.h"
#include "BehaviorTree/BehaviorTree.h"



ADragonAIController::ADragonAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
}

void ADragonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ADragon* Dragon = Cast<ADragon>(InPawn);
	if (Dragon)
	{
		if (Dragon->DragonBT && Dragon->DragonBT->BlackboardAsset)
		{
			BBComponent->InitializeBlackboard(*(Dragon->DragonBT->BlackboardAsset));
			BTComponent->StartTree(*(Dragon->DragonBT));
		}
	}
}

void ADragonAIController::OnUnPossess()
{
	UE_LOG(LogClass, Warning, TEXT("OnUnPossess"));
	BTComponent->StopTree();

	Super::OnUnPossess();
}


void ADragonAIController::SetCurrentState(EDragonState NewState)
{
	if (BBComponent)
	{
		BBComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)NewState);
	}
}

void ADragonAIController::SetTarget(FVector NewLocation)
{
	if (BBComponent)
	{
		BBComponent->SetValueAsVector(TEXT("Target"), NewLocation);
	}
}

void ADragonAIController::SetPlayer(AActor* Player)
{
	if (BBComponent)
	{
		BBComponent->SetValueAsObject(TEXT("Player"), Player);
	}
}
