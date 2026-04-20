// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types/THTypes.h"
#include "THGameMode.generated.h"

class ATHPlayerController;
class ATankEnmey;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChanged, EGamePlayState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelEnd, float, LevelTime);

/**
 * 
 */
UCLASS()
class TANKHERO_API ATHGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    void OnEnemyKilled();
    void OnPlayerDied();
    void HandleNewState(EGamePlayState NewState);

    FOnStateChanged OnStateChanged;
	FOnLevelEnd OnLevelEnd;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "TH|GameMode")
    float PreparationTime = 3.0f;

private:
    EGamePlayState CurrentState = EGamePlayState::None;
    void StartGame();
    void HandleResult();
    void SetTanksActive(bool bIsActive);

    float StartTime;
    int32 TotalEnemies;
    TArray<AActor*> Enemies;
    TWeakObjectPtr<ATHPlayerController> PlayerController;

    FTimerHandle ResultTimer;
};
