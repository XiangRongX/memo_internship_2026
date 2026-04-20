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

	MainMenuWidget->OnStartClicked.AddDynamic(this, &ThisClass::ShowLevelMenu);
	MainMenuWidget->OnSettingsClicked.AddDynamic(this, &ThisClass::ShowSettingsMenu);

	SettingsWidget->OnReturnClicked.AddDynamic(this, &ThisClass::ShowMainMenu);
}

void ALobbyHUD::ShowMainMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	LevelMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void ALobbyHUD::ShowLevelMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	LevelMenuWidget->SetVisibility(ESlateVisibility::Visible);
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void ALobbyHUD::ShowSettingsMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	LevelMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	SettingsWidget->SetVisibility(ESlateVisibility::Visible);
}
