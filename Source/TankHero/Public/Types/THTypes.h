#pragma once

#include "CoreMinimal.h"
#include "THTypes.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Normal      UMETA(DisplayName = "Normal Cannon"),
    Double      UMETA(DisplayName = "Double Cannon"),
    Laser       UMETA(DisplayName = "Laser Beam"),
    Sonic       UMETA(DisplayName = "Sonic Wave")
};

UENUM(BlueprintType)
enum class EGamePlayState : uint8
{
    Preparation,
    Playing,
    Win,
    Lose,
    Pause,
    None
};