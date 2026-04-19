// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOverlay.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TANKHERO_API UTHOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Level;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Pause;
};
