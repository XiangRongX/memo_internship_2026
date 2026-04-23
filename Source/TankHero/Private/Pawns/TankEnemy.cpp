// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Actors/TriggerWall.h"
#include "GameFramework/FloatingPawnMovement.h" 
#include "Actors/THProjectile.h"
#include "Actors/SonicProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Game/THGameMode.h"
#include "Actors/THCameraManager.h"
#include "TankHero/TankHero.h"

ATankEnemy::ATankEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATankEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetChassisVector.IsNearlyZero())
	{
		FRotator TargetRot = UKismetMathLibrary::MakeRotFromX(TargetChassisVector);
		FRotator CurrentRot = GetActorRotation();
		FRotator SmoothedRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, ChassisRotateSpeed);
		SetActorRotation(SmoothedRot);
	}

	FVector TurretLocation = Mesh->GetSocketLocation(TEXT("Tank_Body_BHead"));
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(TurretLocation, TargetTurretLocation);
	FRotator CurrentLocalRot = TurretRelativeRotation;
	FRotator TargetLocalRot = UKismetMathLibrary::NormalizedDeltaRotator(LookAtRot, GetActorRotation());

	TurretRelativeRotation = FMath::RInterpTo(CurrentLocalRot, TargetLocalRot, DeltaTime, TurretRotateSpeed);
	TurretRelativeRotation.Pitch = 0.f;
	TurretRelativeRotation.Roll = 0.f;
}

float ATankEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	FVector HitDir = DamageCauser->GetActorLocation() - GetActorLocation();
	HitDir.Normalize();
	FVector LocalHitDir = GetActorQuat().UnrotateVector(HitDir);
	float Angle = FMath::RadiansToDegrees(FMath::Atan2(LocalHitDir.Y, LocalHitDir.X));

	FName SectionName = FName("Front");
	if (Angle >= -45.f && Angle <= 45.f)        SectionName = FName("Front");
	else if (Angle > 45.f && Angle <= 135.f)    SectionName = FName("Right");
	else if (Angle < -45.f && Angle >= -135.f)  SectionName = FName("Left");
	else                                        SectionName = FName("Back");

	if (HitMontage)
	{
		Mesh->GetAnimInstance()->Montage_Play(HitMontage);
		Mesh->GetAnimInstance()->Montage_JumpToSection(SectionName, HitMontage);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ATankEnemy::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    AAIController* AIC = Cast<AAIController>(NewController);
    if (AIC)
    {
        AIC->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
        AIC->RunBehaviorTree(BehaviorTree);
    }
}

void ATankEnemy::HandleDeath()
{
	if (DeathEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation());
	}

	if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
	{
		if (ATHGameMode* THGameMode = Cast<ATHGameMode>(GameMode))
		{
			THGameMode->OnEnemyKilled();
		}
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (ATHCameraManager* CameraManager = Cast<ATHCameraManager>(PlayerController->PlayerCameraManager))
		{
			CameraManager->PlayExplosionShake(1.0f);
		}
	}

	Destroy();
}

void ATankEnemy::Fire()
{
	if (FireMontage)
	{
		Mesh->GetAnimInstance()->Montage_Play(FireMontage);
	}

	switch (CurrentWeaponType)
	{
	case EWeaponType::Normal:
		FireNormal();
		break;
	case EWeaponType::Double:
		FireDouble();
		break;
	case EWeaponType::Laser:
		FireLaser();
		break;
	case EWeaponType::Sonic:
		FireSonic();
		break;
	}
}

void ATankEnemy::FireNormal()
{
	if (!NormalProjectileClass) return;

	FVector SpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle"));
	FRotator SpawnRotation = Mesh->GetSocketRotation(TEXT("Muzzle"));
	SpawnRotation.Pitch = 0.f;
	SpawnRotation.Roll = 0.f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	ATHProjectile* Projectile = GetWorld()->SpawnActor<ATHProjectile>(NormalProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void ATankEnemy::FireDouble()
{
	if (!NormalProjectileClass) return;

	FVector LeftSpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle_L"));
	FVector RightSpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle_R"));
	FRotator SpawnRotation = Mesh->GetSocketRotation(TEXT("Muzzle"));
	SpawnRotation.Pitch = 0.f;
	SpawnRotation.Roll = 0.f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	ATHProjectile* Projectile1 = GetWorld()->SpawnActor<ATHProjectile>(NormalProjectileClass, LeftSpawnLocation, SpawnRotation, SpawnParams);
	ATHProjectile* Projectile2 = GetWorld()->SpawnActor<ATHProjectile>(NormalProjectileClass, RightSpawnLocation, SpawnRotation, SpawnParams);

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void ATankEnemy::FireLaser()
{
	FVector Start = Mesh->GetSocketLocation(TEXT("Muzzle"));
	FRotator Rotation = Mesh->GetSocketRotation(TEXT("Muzzle"));
	Rotation.Pitch = 0.f;
	Rotation.Roll = 0.f;
	FVector Direction = Rotation.Vector();
	FVector End = Start + (Direction * 5000.f);
	FVector ActualEnd = End;

	TArray<FHitResult> OutHits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceMultiByChannel(OutHits, Start, End, ECC_Laser, Params);
	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			if (Hit.GetActor()->IsRootComponentStatic() || Hit.GetActor()->ActorHasTag("Wall"))
			{
				ActualEnd = Hit.ImpactPoint;

				if (ATriggerWall* TriggerWall = Cast<ATriggerWall>(Hit.GetActor()))
				{
					TriggerWall->TriggerLowering();
				}

				break;
			}
			if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("Player"))
			{
				UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, GetController(), this, nullptr);
				if (ImpactEffect) 
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(),
						ImpactEffect,
						Hit.Location, 
						Hit.ImpactNormal.Rotation() 
					);
				}
			}
		}
	}

	if (LaserEffect)
	{
		UNiagaraComponent* LaserComp = UNiagaraFunctionLibrary::SpawnSystemAttached(LaserEffect, Mesh, FName("Muzzle"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
		if (LaserComp)
		{
			LaserComp->SetVariableVec3(TEXT("Beam End"), ActualEnd);
		}
	}

	if (LaserSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaserSound, GetActorLocation());
	}
}

void ATankEnemy::FireSonic()
{
	if (!SonicProjectileClass) return;

	FVector SpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle"));
	FRotator SpawnRotation = Mesh->GetSocketRotation(TEXT("Muzzle"));
	SpawnRotation.Pitch = 0.f;
	SpawnRotation.Roll = 0.f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<ASonicProjectile>(SonicProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (SonicSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SonicSound, GetActorLocation());
	}
}