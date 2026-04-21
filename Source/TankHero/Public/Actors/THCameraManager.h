// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "THCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API ATHCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
    void PlayExplosionShake(float Scale = 1.0f);
	
protected:
    UPROPERTY(EditAnywhere, Category = "TH|Camera")
    TSubclassOf<UCameraShakeBase> ExplosionShakeClass;
};
