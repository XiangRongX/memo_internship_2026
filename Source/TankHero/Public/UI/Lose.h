// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Lose.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TANKHERO_API ULose : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Time;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Return;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Restart;
};
