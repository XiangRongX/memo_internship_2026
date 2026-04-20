// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"

class UMainMenu;
class ULevelMenu;
class USetting;

/**
 * 
 */
UCLASS()
class TANKHERO_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()
	
public:


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	TSubclassOf<UMainMenu> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	TSubclassOf<ULevelMenu> LevelMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<ULevelMenu> LevelMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	TSubclassOf<USetting> SettingsWidgetClass;

	UPROPERTY()
	TObjectPtr<USetting> SettingsWidget;

private:
	UFUNCTION()
	void ShowMainMenu();

	UFUNCTION()
	void ShowLevelMenu();

	UFUNCTION()
	void ShowSettingsMenu();

};
