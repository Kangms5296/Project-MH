// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItemBase.h"
#include "../../../Battle/Character/Player/PlayerBase.h"
#include "DropItemNameWidgetBase.h"
#include "LookAtPlayerComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Net/UnrealNetwork.h"

#include "../../../Battle/BattleGM.h"
//#include "../../../Test/TestGM.h"

// Sets default values
ADropItemBase::ADropItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetSphereRadius(150.0f);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	LAP = CreateDefaultSubobject<ULookAtPlayerComponent>(TEXT("LAP"));
	LAP->SetupAttachment(RootComponent);

	NameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameWidget"));
	NameWidget->SetupAttachment(LAP);

	bReplicates = true;
}

// Called when the game starts or when spawned
void ADropItemBase::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADropItemBase::ProcessBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADropItemBase::ProcessEndOverlap);
}

// Called every frame
void ADropItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADropItemBase, ItemData);
}

void ADropItemBase::OnRep_ItemData()
{
	FStreamableManager Loader;
	StaticMesh->SetStaticMesh(Loader.LoadSynchronous<UStaticMesh>(ItemData.ItemStaticMesh));

	float MeshHeight = StaticMesh->GetStaticMesh()->GetBounds().GetBox().GetSize().Z;
	LAP->SetRelativeLocation(FVector(0, 0, 30 + MeshHeight));

	if (NameWidget)
	{
		UDropItemNameWidgetBase* NameWidgetValue = Cast<UDropItemNameWidgetBase>(NameWidget->GetUserWidgetObject());
		if (NameWidgetValue)
		{
			NameWidgetValue->InitWidget();

			NameWidgetValue->SetName(ItemData.ItemName);
			NameWidgetValue->SetBgColor(FLinearColor(0, 0, 0, 0.8f));

			NameWidget->SetVisibility(true);
		}
	}
}

void ADropItemBase::Init(FItemDataTable NewData)
{
	ItemData = NewData;

	OnRep_ItemData();
}

void ADropItemBase::ProcessBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		APlayerBase* Player = Cast<APlayerBase>(OtherActor);
		if (Player && Player->IsLocallyControlled())
		{
			Player->AddNearItem(this);
		}
	}
}

void ADropItemBase::ProcessEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		APlayerBase* Player = Cast<APlayerBase>(OtherActor);
		if (Player && Player->IsLocallyControlled())
		{
			Player->SubNearItem(this);
		}
	}
}

void ADropItemBase::SetHighlight(bool NewHighlight)
{
	if (NameWidget)
	{
		UDropItemNameWidgetBase* NameWidgetValue = Cast<UDropItemNameWidgetBase>(NameWidget->GetUserWidgetObject());
		if (NameWidgetValue)
		{
			if (NewHighlight)
			{
				NameWidgetValue->SetBgColor(FLinearColor(1, 0.2f, 0, 0.4f));
			}
			else
			{
				NameWidgetValue->SetBgColor(FLinearColor(0, 0, 0, 0.8f));
			}
		}
	}
}

