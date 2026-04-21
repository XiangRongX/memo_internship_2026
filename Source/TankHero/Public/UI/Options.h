// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Options.generated.h"

class UCheckBox;

/**
 * 
 */
UCLASS()
class TANKHERO_API UOptions : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CheckBox_Sound;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CheckBox_Music;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CheckBox_Follow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CheckBox_Vibrate;

private:
	UFUNCTION()
	void OnSoundCheckBoxChanged(bool bIsChecked);

	UFUNCTION()
	void OnMusicCheckBoxChanged(bool bIsChecked);

	UFUNCTION()
	void OnFollowCheckBoxChanged(bool bIsChecked);

	UFUNCTION()
	void OnVibrateCheckBoxChanged(bool bIsChecked);
};
