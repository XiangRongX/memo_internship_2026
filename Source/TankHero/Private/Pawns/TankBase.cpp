// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h" 
#include "Components/HealthBarWidgetComponent.h"

ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCanEverAffectNavigation(false);
	Capsule->CanCharacterStepUpOn = ECB_No;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("TankMovementComponent"));
	MovementComponent->MaxSpeed = 500.f;
	MovementComponent->Acceleration = 2000.f;
	MovementComponent->Deceleration = 4000.f; 
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));

	HealthBarWidgetComponent = CreateDefaultSubobject<UHealthBarWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);

	Health = MaxHealth;
}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = Speed;
	}
}

void ATankBase::HandleDeath()
{

}

void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATankBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= ActualDamage;
	HealthBarWidgetComponent->UpdateHealth(Health, MaxHealth);
	if(Health <= 0.f)
	{
		HandleDeath();
	}

	return ActualDamage;
}


