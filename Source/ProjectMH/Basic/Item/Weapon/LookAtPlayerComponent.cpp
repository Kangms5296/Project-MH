// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtPlayerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULookAtPlayerComponent::ULookAtPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TArray<USceneComponent*> ChildComponents;
	GetChildrenComponents(false, ChildComponents);
	for (USceneComponent* ChildComponent : ChildComponents)
	{
		FRotator NewRot = ChildComponent->GetRelativeRotation();
		ChildComponent->SetRelativeRotation(FRotator(NewRot.Pitch, NewRot.Yaw + 180, NewRot.Roll));
	}
}


// Called every frame
void ULookAtPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ÀÌ ÄÄÆ÷³Í
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FRotator NewRot = FRotator(PC->PlayerCameraManager->GetCameraRotation().Pitch, PC->PlayerCameraManager->GetCameraRotation().Yaw, PC->PlayerCameraManager->GetCameraRotation().Roll);
		SetRelativeRotation(NewRot);
	}
}

