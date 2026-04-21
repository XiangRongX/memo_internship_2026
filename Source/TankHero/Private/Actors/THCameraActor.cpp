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
    UTHGameInstance* GI = Cast<UTHGameInstance>(GetGameInstance());

    // 定义我们要平滑达到的目标值
    FVector TargetRootLoc;
    FRotator TargetRotation;
    float TargetArmLen;

    if (GI && GI->IsFollowEnabled())
    {
        // 1. 【跟随模式】的逻辑
        // 位置计算
        TargetRootLoc = FVector(
            FMath::Clamp(TankLoc.X, -MoveLimit, MoveLimit),
            FMath::Clamp(TankLoc.Y, -MoveLimit, MoveLimit),
            CameraRootLoc.Z
        );

        // 转向计算 (反向 Yaw)
        FVector Offset = TankLoc - CameraRootLoc;
        float TargetYaw = FMath::Clamp(Offset.Y * -0.02f, -15.f, 15.f);
        TargetRotation = FRotator(-60.f, TargetYaw, 0.f);

        // 缩放计算 (动态臂长)
        float DistToTank = FVector::DistXY(TankLoc, CameraRootLoc);
        TargetArmLen = FMath::GetMappedRangeValueClamped(
            FVector2D(0.f, MoveLimit),
            FVector2D(MinArmLength, MaxArmLength),
            DistToTank
        );
    }
    else
    {
        // 2. 【固定模式】的逻辑 (强制回归默认)
        TargetRootLoc = FVector(-MoveLimit, 0.f, CameraRootLoc.Z); // 回原点
        TargetRotation = FRotator(-60.f, 0.f, 0.f);         // 恢复正视
        TargetArmLen = MaxArmLength;                             // 恢复默认高度 (或者是你的 MinArmLength)
    }

    // --- 统一执行平滑插值 (放在外面保证切换时过渡自然) ---

    // 应用位置
    SetActorLocation(FMath::VInterpTo(CameraRootLoc, TargetRootLoc, DeltaTime, 3.0f));

    // 应用旋转
    SpringArm->SetWorldRotation(FMath::RInterpTo(SpringArm->GetComponentRotation(), TargetRotation, DeltaTime, 2.0f));

    // 应用臂长
    SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetArmLen, DeltaTime, 2.0f);
}

