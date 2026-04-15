// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SonicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Actors/TriggerWall.h"
#include "TankHero/TankHero.h"
#include "Pawns/TankBase.h"

ASonicProjectile::ASonicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	ProjectileEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileEffect"));
	ProjectileEffect->SetupAttachment(RootComponent);
	ProjectileEffect->bAutoActivate = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->ProjectileGravityScale = 0.f;

}

void ASonicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(2.f);
	if(ProjectileEffect)
	{
		ProjectileEffect->SetVariableFloat(FName("_Size"), 1.f);
	}

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
}

void ASonicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileEffect)
	{
		float CurrentAge = GetGameTimeSinceCreation();
		float Alpha = FMath::Clamp(CurrentAge / 2.0f, 0.0f, 1.0f);
		float NewSize = FMath::Lerp(1.0f, 3.0f, Alpha);
		ProjectileEffect->SetVariableFloat(FName("_Size"), NewSize);

		float NewRadius = FMath::Lerp(50.0f, 150.0f, Alpha);
		Sphere->SetSphereRadius(NewRadius);
	}
}

void ASonicProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetOwner() || DamagedActors.Contains(OtherActor)) return;

	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		if (ATankBase* Tank = Cast<ATankBase>(GetOwner()))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Tank->GetDamage(), GetInstigatorController(), this, UDamageType::StaticClass());
		}
		
		if(ImpactEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, SweepResult.ImpactPoint, SweepResult.ImpactNormal.Rotation());
		}
	}
}
