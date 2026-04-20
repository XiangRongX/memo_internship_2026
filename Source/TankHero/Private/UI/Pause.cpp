// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pause.h"
#include "UI/Options.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Game/THGameMode.h"

void UPause::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_Resume)
	{
		Button_Resume->OnClicked.AddDynamic(this, &ThisClass::OnResumeButtonClicked);
	}
	if(Button_Quit)
	{
		Button_Quit->OnClicked.AddDynamic(this, &ThisClass::OnQuitButtonClicked);
	}
	if(Button_Restart)
	{
		Button_Restart->OnClicked.AddDynamic(this, &ThisClass::OnRestartButtonClicked);
	}
}

void UPause::OnResumeButtonClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	if (ATHGameMode* Gamemode = Cast<ATHGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		Gamemode->HandleNewState(EGamePlayState::Playing);
	}
	RemoveFromParent();
}

void UPause::OnRestartButtonClicked()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}

void UPause::OnQuitButtonClicked()
{
	//UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
