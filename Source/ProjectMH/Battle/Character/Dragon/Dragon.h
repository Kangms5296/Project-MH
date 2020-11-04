// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dragon.generated.h"

UENUM(BlueprintType)
enum class EDragonState : uint8
{
	Normal = 0	UMETA(Display = "Normal"),
	Battle = 1	UMETA(Display = "Battle"),
	Chase = 2	UMETA(Display = "Chase"),
	Dead = 3	UMETA(Display = "Dead"),
};

UCLASS()
class PROJECTMH_API ADragon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADragon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere)
		class UPawnSensingComponent* PawnSensing;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		EDragonState CurrentState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float CurrentHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float MaxHP = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float WalkSpeed = 150.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float RunSpeed = 300.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float Attack = 30.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AttackRange = 100.0f;

	virtual float TakeDamage(float DamageAmout, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void ProcessSeenPawn(APawn* Pawn);

	UFUNCTION()
		void ProcessHeardPawn(APawn* Pawn, const FVector& Location, float Volume);

	UFUNCTION(BlueprintCallable)
		void SetCurrentState(EDragonState NewState);

	UFUNCTION(BlueprintCallable)
		void SetSpeed(float Speed);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		class UBehaviorTree* DragonBT;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		class UParticleSystem* SpitFire;


	UFUNCTION(BlueprintCallable)
		void DragonSpitFire();

	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		TSubclassOf<class ANewFireBall> FireBallClass;

};
