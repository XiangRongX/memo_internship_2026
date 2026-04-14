// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickupBase.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankHero/TankHero.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    RootComponent = Sphere;
    Sphere->SetSphereRadius(50.f);
    Sphere->SetCollisionProfileName(TEXT("Trigger"));
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Sphere->SetCollisionResponseToChannel(ECC_Player, ECollisionResponse::ECR_Overlap);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Sphere);
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
    Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
}

void APickupBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(FName("Player"))) return;

    if (PickupEffect)
    {
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PickupEffect, GetActorLocation());
    }
    if (PickupSound)
    {
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
    }

	Destroy();
}

void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!Effect) return;

    Effect->AddLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));

    RunningTime += DeltaTime;
    float DeltaZ = FMath::Sin(RunningTime * FloatFrequency) * FloatAmplitude;
    FVector NewLocation = InitialVisualLocation;
    NewLocation.Z += DeltaZ;
    Effect->SetRelativeLocation(NewLocation);
}

