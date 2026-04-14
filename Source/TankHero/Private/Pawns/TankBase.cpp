// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h" 

ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("TankMovementComponent"));
	MovementComponent->MaxSpeed = 800.f;
	MovementComponent->Acceleration = 2000.f;
	MovementComponent->Deceleration = 4000.f; 
}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = Speed;
	}
}

void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


