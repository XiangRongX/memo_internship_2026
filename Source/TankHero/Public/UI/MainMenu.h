// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

/**
 * 
 */
UCLASS()
class TANKHERO_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	FOnButtonClicked OnStartClicked;
	FOnButtonClicked OnSettingsClicked;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Start;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Settings;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Quit;

private:
	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnSettingsButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();
};
