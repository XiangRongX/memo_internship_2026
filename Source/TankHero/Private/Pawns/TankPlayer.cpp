// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/THPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

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
