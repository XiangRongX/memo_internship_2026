// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/THPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/THProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Actors/TriggerWall.h"
#include "Actors/SonicProjectile.h"

ATankPlayer::ATankPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1000.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	LeftWheel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftWheel"));
	LeftWheel->SetupAttachment(Mesh);
	RightWheel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightWheel"));
	RightWheel->SetupAttachment(Mesh);

}

void ATankPlayer::Tick(float DeltaTime)
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

void ATankPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ATHPlayerController>(GetController());
}

void ATankPlayer::FireNormal()
{
	if (!NormalProjectileClass) return;

	FVector SpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle"));
	FRotator SpawnRotation = Mesh->GetSocketRotation(TEXT("Muzzle"));
	SpawnRotation.Pitch = 0.f;
	SpawnRotation.Roll = 0.f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	GetWorld()->SpawnActor<ATHProjectile>(NormalProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void ATankPlayer::FireDouble()
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
	GetWorld()->SpawnActor<ATHProjectile>(NormalProjectileClass, LeftSpawnLocation, SpawnRotation, SpawnParams);
	GetWorld()->SpawnActor<ATHProjectile>(NormalProjectileClass, RightSpawnLocation, SpawnRotation, SpawnParams);

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void ATankPlayer::FireLaser()
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

	bool bHit = GetWorld()->LineTraceMultiByChannel(OutHits, Start, End, ECC_Visibility, Params);
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
			if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("Enemy"))
			{
				UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, GetController(), this, nullptr);
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

void ATankPlayer::FireSonic()
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

void ATankPlayer::Fire()
{
	if (!bCanFire) return;

	if(FireMontage)
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

	bCanFire = false;
	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &ThisClass::ResetFire, FireCooldown);
}
