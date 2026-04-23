// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/THGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Player/THPlayerController.h"
#include "Pawns/TankEnemy.h"
#include "Game/THGameInstance.h"
#include "Actors/THCameraActor.h"

void ATHGameMode::OnEnemyKilled()
{
    TotalEnemies--;
    if (TotalEnemies <= 0)
    {
        HandleNewState(EGamePlayState::Win);
    }
}

void ATHGameMode::OnPlayerDied()
{
    HandleNewState(EGamePlayState::Lose);
}

void ATHGameMode::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = Cast<ATHPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    AActor* FoundCamera = UGameplayStatics::GetActorOfClass(this, ATHCameraActor::StaticClass());

    if (PlayerController.IsValid() && FoundCamera)
    {
        PlayerController->SetViewTarget(FoundCamera);
    }

    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), Enemies);
    TotalEnemies = Enemies.Num();

    HandleNewState(EGamePlayState::Preparation);

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::StartGame, PreparationTime, false);
}

void ATHGameMode::HandleNewState(EGamePlayState NewState)
{
    if (CurrentState == NewState) return;
    CurrentState = NewState;

    switch (CurrentState)
    {
    case EGamePlayState::Preparation:
        SetTanksActive(false);
        break;

    case EGamePlayState::Playing:
        SetTanksActive(true);
        StartTime = GetWorld()->GetTimeSeconds();
        if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
        {
            THGameInstance->SwitchMusicState(EMusicState::Level);
        }
        break;

    case EGamePlayState::Pause:
        {
            FInputModeUIOnly InputMode;
            if (PlayerController.IsValid())
            {
                PlayerController->SetInputMode(InputMode);
            }
            if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
            {
                THGameInstance->SwitchMusicState(EMusicState::None);
            }
            UGameplayStatics::SetGamePaused(GetWorld(), true);
            break;
        }

    case EGamePlayState::Win:
        {
            FInputModeUIOnly InputMode;
            if (PlayerController.IsValid())
            {
                PlayerController->SetInputMode(InputMode);
            }
            float FinalTime = GetWorld()->GetTimeSeconds() - StartTime;
            GetWorldTimerManager().SetTimer(ResultTimer, this, &ThisClass::HandleResult, 1.f, false);
            OnLevelEnd.Broadcast(FinalTime);
            if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
            {
                int32 CurrentLevel = THGameInstance->GetCurrentLevel();
                if (CurrentLevel == 15)
                {
                    OnLastLevel.Broadcast();
                    THGameInstance->SwitchMusicState(EMusicState::Win);
                    return;
                }
                THGameInstance->SetMaxLevel(CurrentLevel + 1);
                THGameInstance->SwitchMusicState(EMusicState::Win);
            }
            return;
        }
    case EGamePlayState::Lose:
        {
            FInputModeUIOnly InputMode;
            if (PlayerController.IsValid())
            {
                PlayerController->SetInputMode(InputMode);
            }
            float FinalTime = GetWorld()->GetTimeSeconds() - StartTime;
            GetWorldTimerManager().SetTimer(ResultTimer, this, &ThisClass::HandleResult, 1.f, false);
            OnLevelEnd.Broadcast(FinalTime);
            if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
            {
                THGameInstance->SwitchMusicState(EMusicState::Lose);
            }
            return;
        }
    }

    OnStateChanged.Broadcast(NewState);
}

void ATHGameMode::StartGame()
{
    HandleNewState(EGamePlayState::Playing);
}

void ATHGameMode::HandleResult()
{
    UGameplayStatics::SetGamePaused(GetWorld(), true);
    OnStateChanged.Broadcast(CurrentState);
}

void ATHGameMode::SetTanksActive(bool bIsActive)
{
    if (PlayerController.IsValid())
    {
        if (bIsActive)
        {
            FInputModeGameAndUI InputMode;
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
            InputMode.SetHideCursorDuringCapture(false);
            PlayerController->SetInputMode(InputMode);
            PlayerController->SetCanRotate(true);
        }
        else
        {
            FInputModeUIOnly InputMode;
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputMode);
            PlayerController->SetCanRotate(false);
        }
    }

    for (AActor* EnemyActor : Enemies)
    {
        APawn* EnemyPawn = Cast<APawn>(EnemyActor);
        if (!EnemyPawn) continue;

        if (AAIController* AIC = Cast<AAIController>(EnemyPawn->GetController()))
        {
            if (UBrainComponent* Brain = AIC->GetBrainComponent())
            {
                if (bIsActive)
                {
                    Brain->RestartLogic();
                    EnemyPawn->SetActorTickEnabled(true);
                }
                else
                {
                    Brain->StopLogic(TEXT("GamePaused"));
                    EnemyPawn->SetActorTickEnabled(false);
                }
            }
        }
    }

}
