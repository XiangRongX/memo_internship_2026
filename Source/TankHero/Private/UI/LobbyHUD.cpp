// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyHUD.h"
#include "UI/MainMenu.h"
#include "UI/LevelMenu.h"
#include "UI/Setting.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();
	
	MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuWidgetClass);
	LevelMenuWidget = CreateWidget<ULevelMenu>(GetWorld(), LevelMenuWidgetClass);
	SettingsWidget = CreateWidget<USetting>(GetWorld(), SettingsWidgetClass);

	MainMenuWidget->AddToViewport();
	LevelMenuWidget->AddToViewport();
	SettingsWidget->AddToViewport();

	LevelMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}
