// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Dragon.h"
#include "DragonAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API UDragonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		EDragonState CurrentState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float Speed;

	//UFUNCTION()
	//void AnimNotify_Checkattack2(UAnimNotify* Notify);



};
