// Fill out your copyright notice in the Description page of Project Settings.

#include "Dragon.h"
#include "NewFireBall.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DragonAIController.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
ADragon::ADragon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));
	//GetMesh()->GetSocketByName(TEXT("FirePoint"));



	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));

}

// Called when the game starts or when spawned
void ADragon::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;

	SetSpeed(WalkSpeed);
	SetCurrentState(EDragonState::Normal);

	if (PawnSensing) {
		PawnSensing->OnSeePawn.AddDynamic(this, &ADragon::ProcessSeenPawn);
		PawnSensing->OnHearNoise.AddDynamic(this, &ADragon::ProcessHeardPawn);
	}



}

// Called every frame
void ADragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ADragon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (CurrentHP <= 0)
	{
		return 0.0f;
	}

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))	//PointDamage Ã³¸®
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);

		UE_LOG(LogClass, Warning, TEXT("Point Damage %s"), *(PointDamageEvent->HitInfo.BoneName.ToString()));

		if (PointDamageEvent->HitInfo.BoneName.Compare(TEXT("head")) == 0)
		{
			CurrentHP = 0;
		}
		else
		{
			CurrentHP -= DamageAmount;
		}
	}

	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);

		UE_LOG(LogClass, Warning, TEXT("Radial Damage %f"), DamageAmount);
	}
	else
	{
		CurrentHP -= DamageAmount;
	}

	if (CurrentHP <= 0)
	{
		SetCurrentState(EDragonState::Dead);
	}
	UE_LOG(LogClass, Warning, TEXT("%f"), DamageAmount);

	return 0.0f;

}

void ADragon::ProcessSeenPawn(APawn* Pawn)
{
	if (CurrentState == EDragonState::Normal)
	{
		UE_LOG(LogClass, Warning, TEXT("See %s"), *Pawn->GetName());
		SetCurrentState(EDragonState::Chase);

		ADragonAIController* AIC = GetController<ADragonAIController>();
		if (AIC)
		{
			AIC->SetPlayer(Pawn);

		}
	}
}

void ADragon::ProcessHeardPawn(APawn* Pawn, const FVector& Location, float Volume)
{
}

void ADragon::SetCurrentState(EDragonState NewState)
{
	CurrentState = NewState;

	ADragonAIController* AIC = GetController<ADragonAIController>();
	if (AIC)
	{
		AIC->SetCurrentState(NewState);
	}
}

void ADragon::SetSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void ADragon::DragonSpitFire()
{
	ANewFireBall* Test = GetWorld()->SpawnActor<ANewFireBall>(FireBallClass, GetMesh()->GetSocketTransform(TEXT("FirePoint")));
}



