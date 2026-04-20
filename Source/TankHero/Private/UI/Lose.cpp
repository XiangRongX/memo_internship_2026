// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lose.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULose::SetTimeText(float Time)
{
	int32 Minutes = FMath::FloorToInt(Time / 60.f);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(Time, 60.f));
	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	if (TextBlock_Time)
	{
		TextBlock_Time->SetText(FText::FromString(TimeString));
	}
}

void ULose::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_Return)
	{
		Button_Return->OnClicked.AddDynamic(this, &ThisClass::OnReturnButtonClicked);
	}
	if(Button_Restart)
	{
		Button_Restart->OnClicked.AddDynamic(this, &ThisClass::OnRestartButtonClicked);
	}
}

void ULose::OnReturnButtonClicked()
{
	//UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void ULose::OnRestartButtonClicked()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}
