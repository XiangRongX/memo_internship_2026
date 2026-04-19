// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Pause.generated.h"

class UButton;
class UOptions;

/**
 * 
 */
UCLASS()
class TANKHERO_API UPause : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Resume;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Restart;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Quit;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptions> WBP_Options;
};
