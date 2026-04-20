// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_Start)
	{
		Button_Start->OnClicked.AddDynamic(this, &ThisClass::OnStartButtonClicked);
	}
	if(Button_Settings)
	{
		Button_Settings->OnClicked.AddDynamic(this, &ThisClass::OnSettingsButtonClicked);
	}
	if(Button_Quit)
	{
		Button_Quit->OnClicked.AddDynamic(this, &ThisClass::OnQuitButtonClicked);
	}
}

void UMainMenu::OnStartButtonClicked()
{
	OnStartClicked.Broadcast();
}

void UMainMenu::OnSettingsButtonClicked()
{
	OnSettingsClicked.Broadcast();
}

void UMainMenu::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}