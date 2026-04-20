// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Win.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Game/THGameInstance.h"

void UWin::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(Button_Return)
	{
		Button_Return->OnClicked.AddDynamic(this, &ThisClass::OnReturnButtonClicked);
	}
	if(Button_Next)
	{
		Button_Next->OnClicked.AddDynamic(this, &ThisClass::OnNextButtonClicked);
	}
	if(Button_Restart)
	{
		Button_Restart->OnClicked.AddDynamic(this, &ThisClass::OnRestartButtonClicked);
	}
}

void UWin::OnReturnButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Lobby"));
}

void UWin::OnNextButtonClicked()
{
	if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
	{
		int32 CurrentLevel = THGameInstance->GetCurrentLevel();
		THGameInstance->SetCurrentLevel(CurrentLevel + 1);
		FString NextLevelName = FString::Printf(TEXT("Level%d"), CurrentLevel + 1);
		UGameplayStatics::OpenLevel(this, FName(*NextLevelName));
	}

}

void UWin::OnRestartButtonClicked()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}

void UWin::SetTimeText(float Time)
{
	int32 Minutes = FMath::FloorToInt(Time / 60.f);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(Time, 60.f));
	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	if (TextBlock_Time)
	{
		TextBlock_Time->SetText(FText::FromString(TimeString));
	}
}
