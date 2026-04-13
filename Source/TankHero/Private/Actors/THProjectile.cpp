// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/THProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Actors/TriggerWall.h"
#include "TankHero/TankHero.h"

ATHProjectile::ATHProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionProfileName(FName("BlockAll"));

	ProjectileEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileEffect"));
	ProjectileEffect->SetupAttachment(RootComponent);
	ProjectileEffect->bAutoActivate = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.f;
	ProjectileMovement->Friction = 0.f;
	ProjectileMovement->BounceVelocityStopSimulatingThreshold = 0.f;
}

void ATHProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentHit.AddDynamic(this, &ATHProjectile::OnHit);
}

void ATHProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->ActorHasTag("Enemy"))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
			Destroy(); 
			return;
		}

		CurrentBounces++;
		if (CurrentBounces > MaxBounces)
		{
			Destroy();
		}

		if (ATriggerWall* TiggerWall = Cast<ATriggerWall>(OtherActor))
		{
			TiggerWall->TriggerLowering();
		}
	}
}

void ATHProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHProjectile::Destroyed()
{
	if (DestroyEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DestroyEffect, GetActorLocation(), GetActorRotation());
	}

	Super::Destroyed();
}

