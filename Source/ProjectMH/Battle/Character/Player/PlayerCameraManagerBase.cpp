// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraManagerBase.h"
#include "PlayerBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../../Basic/Item/Weapon/WeapomComponent.h"

APlayerCameraManagerBase::APlayerCameraManagerBase()
{

}

void APlayerCameraManagerBase::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	APlayerBase* Pawn = GetOwningPlayerController()->GetPawn<APlayerBase>();

	if (Pawn)
	{
		if (Pawn->Weapon->CurrentWeaponData.WeaponType == EWeaponType::Gun)
		{
			float TargetFOV = Pawn->bIsIronsight ? IronsightFOV : NormalFOV;
			float ResultFOV = FMath::FInterpTo(GetFOVAngle(), TargetFOV, DeltaTime, 20.0f);

			SetFOV(ResultFOV);
		}

		// Crouch
		FVector TargetPosition = Pawn->bIsCrouched ? Pawn->CrouchedSpringArmPosition : Pawn->NormalSpringArmPosition;\
		FVector ResultSpringArmPosition = FMath::VInterpTo(Pawn->SpringArm->GetRelativeLocation(), TargetPosition, DeltaTime, 10.0f);
		Pawn->SpringArm->SetRelativeLocation(ResultSpringArmPosition);
	}
}


