// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Setting.generated.h"

class UButton;
class UOptions;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsButtonClicked);

/**
 * 
 */
UCLASS()
class TANKHERO_API USetting : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnSettingsButtonClicked OnReturnClicked;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Return;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptions> WBP_Options;

private:
	UFUNCTION()
	void OnReturnButtonClicked();

};
