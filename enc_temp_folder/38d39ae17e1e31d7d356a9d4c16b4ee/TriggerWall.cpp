// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TriggerWall.h"
#include "Components/BoxComponent.h"

ATriggerWall::ATriggerWall()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

void ATriggerWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATriggerWall::TryResetWall()
{
	TArray<AActor*> OverlappingActors;
	Box->GetOverlappingActors(OverlappingActors, APawn::StaticClass());

	if (OverlappingActors.Num() == 0)
	{
		bIsLowered = false;
		ResetWall();
	}
	else
	{
		GetWorldTimerManager().SetTimer(ResetTimerHandle, this, &ThisClass::TryResetWall, ResetDelay, false);
	}
}

void ATriggerWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerWall::TriggerLowering_Implementation()
{
	if (bIsLowered) return;

	bIsLowered = true;
	GetWorldTimerManager().SetTimer(ResetTimerHandle, this, &ThisClass::TryResetWall, ResetDelay, false);
}

