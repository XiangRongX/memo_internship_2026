// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/THCameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game/THGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

ATHCameraActor::ATHCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    SpringArm->SetUsingAbsoluteRotation(true);
    SpringArm->TargetArmLength = 2000.f;
    SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATHCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (!PlayerPawn) return;

    FVector TankLoc = PlayerPawn->GetActorLocation();
    FVector CameraRootLoc = GetActorLocation();
    FVector TargetRootLoc = CameraRootLoc;
    if (UTHGameInstance* GameInstance = Cast<UTHGameInstance>(GetGameInstance()))
    {
        if (GameInstance->IsFollowEnabled())
        {
            TargetRootLoc = FVector(
                FMath::Clamp(TankLoc.X, -MoveLimit, MoveLimit),
                FMath::Clamp(TankLoc.Y, -MoveLimit, MoveLimit),
                CameraRootLoc.Z
            );
        }
        else
        {
            TargetRootLoc = FVector(0.f, 0.f, CameraRootLoc.Z);
        }
    }
    SetActorLocation(FMath::VInterpTo(CameraRootLoc, TargetRootLoc, DeltaTime, 3.0f));

    FVector Offset = TankLoc - GetActorLocation();
    float TargetYaw = Offset.Y * -0.02f;
    TargetYaw = FMath::Clamp(TargetYaw, -15.f, 15.f);
    FRotator FinalRot = FRotator(-60.f, TargetYaw, 0.f);
    SpringArm->SetWorldRotation(FMath::RInterpTo(SpringArm->GetComponentRotation(), FinalRot, DeltaTime, 2.0f));

    float DistToTank = FVector::DistXY(TankLoc, GetActorLocation());
    float DynamicArmLength = FMath::GetMappedRangeValueClamped(
        FVector2D(0.f, MoveLimit),       
        FVector2D(MinArmLength, MaxArmLength),
        DistToTank
    );
    SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, DynamicArmLength, DeltaTime, 2.0f);
}

