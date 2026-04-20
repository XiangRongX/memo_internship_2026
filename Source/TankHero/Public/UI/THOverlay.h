// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOverlay.generated.h"

class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseButtonClicked);

/**
 * 
 */
UCLASS()
class TANKHERO_API UTHOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPauseButtonVisibility(bool bIsVisible);
	void SetLevelText(int32 Level);

	UFUNCTION(BlueprintImplementableEvent)
	void HideLevelText();

	FOnPauseButtonClicked OnPauseButtonClicked;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Level;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Pause;

	UFUNCTION()
	void OnPauseClicked();
};
