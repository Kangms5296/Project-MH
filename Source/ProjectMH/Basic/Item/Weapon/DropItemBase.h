// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../../../Battle/Item/ItemDataTable.h"

#include "DropItemBase.generated.h"

UCLASS()
class PROJECTMH_API ADropItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ULookAtPlayerComponent* LAP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_ItemData")
	FItemDataTable ItemData;

	UFUNCTION()
	void OnRep_ItemData();

	void Init(FItemDataTable NewData);

	UFUNCTION()
	void ProcessBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ProcessEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetHighlight(bool NewHighlight);
};
