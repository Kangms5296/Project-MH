// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "PlayerCameraManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMH_API APlayerCameraManagerBase : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ABasicPCM();

	virtual void UpdateCamera(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOV")
	float NormalFOV = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOV")
	float IronsightFOV = 60.0f;
};
