#include "PlayerAnimInstance.h"
#include "PlayerBase.h"
#include "../../../Basic/Item/Weapon/WeapomComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APlayerBase* Pawn = Cast<APlayerBase>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Direction = CalculateDirection(Pawn->GetCharacterMovement()->Velocity,
			Pawn->GetActorRotation());

		Speed = Pawn->GetCharacterMovement()->Velocity.Size();

		bIsCrouched = Pawn->bIsCrouched;
		bIsFire = Pawn->bIsFire;
		bIsSprint = Pawn->bIsSprint;
		bIsIronsight = Pawn->bIsIronsight;
		bIsJumping = Pawn->GetCharacterMovement()->IsFalling();
		WeaponType = Pawn->Weapon->CurrentWeaponData.WeaponType;

		FRotator AimRotation = Pawn->GetAimOffset();
		AimYaw = AimRotation.Yaw;
		AimPitch = AimRotation.Pitch;
		/*
		bIsReload = Pawn->bIsReload;

		if (Pawn->ReloadMontage && Pawn->bIsReload)
		{
			if (!Montage_IsPlaying(Pawn->ReloadMontage))
			{
				Pawn->PlayAnimMontage(Pawn->ReloadMontage);
			}
		}
		*/
	}
}

/*
void UPlayerAnimInstance::AnimNotify_ReloadEnd(UAnimNotify* AnimNotify)
{
	APlayerBase* Pawn = Cast<APlayerBase>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		bIsReload = false;
		Pawn->bIsReload = false;
		Pawn->C2S_SetReload(false);

		Pawn->Weapon->CurrentWeaponData.Value4 = Pawn->Weapon->CurrentWeaponData.Value5;
	}
}
*/
