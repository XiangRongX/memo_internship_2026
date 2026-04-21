// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/THCameraManager.h"
#include "Game/THGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

void ATHCameraManager::PlayExplosionShake(float Scale)
{
    UTHGameInstance* GameInstance = Cast<UTHGameInstance>(GetWorld()->GetGameInstance());

    if (GameInstance && GameInstance->IsVibrateEnabled() && ExplosionShakeClass)
    {
        StartCameraShake(ExplosionShakeClass, Scale);
    }
}
