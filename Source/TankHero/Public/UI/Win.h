// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Win.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TANKHERO_API UWin : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetTimeText(float Time);
	void SetNextButtonEnabled(bool bEnabled);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Time;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Return;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Next;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Restart;

private:
	UFUNCTION()
	void OnReturnButtonClicked();

	UFUNCTION()
	void OnNextButtonClicked();

	UFUNCTION()
	void OnRestartButtonClicked();
};
