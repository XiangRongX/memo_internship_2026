// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/THHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/THOverlay.h"
#include "UI/Win.h"
#include "UI/Lose.h"
#include "UI/Pause.h"
#include "Game/THGameInstance.h"
#include "Game/THGameMode.h"
#include "Kismet/GameplayStatics.h"

void ATHHUD::BeginPlay()
{
    Super::BeginPlay();

    THGameMode = Cast<ATHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    THGameMode->OnStateChanged.AddDynamic(this, &ThisClass::HandleStateChanged);
    HandleStateChanged(EGamePlayState::Preparation);
}

void ATHHUD::HandleStateChanged(EGamePlayState NewState)
{
    switch (NewState)
    {
    case EGamePlayState::Preparation:
        ShowWidget(OverlayWidget, OverlayWidgetClass);
        if (UTHOverlay* THOverlay = Cast<UTHOverlay>(OverlayWidget))
        {
			THOverlay->OnPauseButtonClicked.AddDynamic(this, &ThisClass::RequestPause);
            if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
            {
                THOverlay->SetLevelText(THGameInstance->GetCurrentLevel());
            }
        }
        break;

    case EGamePlayState::Playing:
        if (UTHOverlay* THOverlay = Cast<UTHOverlay>(OverlayWidget))
        {
			THOverlay->SetPauseButtonVisibility(true);
            THOverlay->HideLevelText();
        }
        break;

    case EGamePlayState::Win:
        ShowWidget(WinWidget, WinWidgetClass);
        if (UTHOverlay* THOverlay = Cast<UTHOverlay>(OverlayWidget))
        {
			THOverlay->SetPauseButtonVisibility(false);
        }
        break;

    case EGamePlayState::Lose:
        ShowWidget(LoseWidget, LoseWidgetClass);
        if (UTHOverlay* THOverlay = Cast<UTHOverlay>(OverlayWidget))
        {
            THOverlay->SetPauseButtonVisibility(false);
        }
        break;

	case EGamePlayState::Pause:
        ShowWidget(PauseWidget, PauseWidgetClass);
		break;
    }
}

void ATHHUD::ShowWidget(TObjectPtr<UUserWidget>& Instance, TSubclassOf<UUserWidget> Class)
{
    if (!Class) return;

    if (!Instance)
    {
        Instance = CreateWidget<UUserWidget>(GetWorld(), Class);
    }

    if (Instance && !Instance->IsInViewport())
    {
        Instance->AddToViewport();
    }
}

void ATHHUD::RequestPause()
{
	THGameMode->HandleNewState(EGamePlayState::Pause);
}
