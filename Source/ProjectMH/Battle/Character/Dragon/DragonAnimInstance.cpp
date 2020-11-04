// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Dragon.h"
#include "Kismet/GameplayStatics.h"



void UDragonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ADragon* Dragon = Cast<ADragon>(TryGetPawnOwner());

	if (Dragon && Dragon->IsValidLowLevel())
	{
		CurrentState = Dragon->CurrentState;
		Speed = Dragon->GetCharacterMovement()->Velocity.Size();
	}
}
