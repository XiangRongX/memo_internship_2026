// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/THOverlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTHOverlay::SetPauseButtonVisibility(bool bIsVisible)
{
	if (Button_Pause)
	{
		Button_Pause->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UTHOverlay::SetLevelText(int32 Level)
{
	if (TextBlock_Level)
	{
		TextBlock_Level->SetText(FText::AsNumber(Level));
	}
}

void UTHOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_Pause)
	{
		Button_Pause->SetVisibility(ESlateVisibility::Hidden);
	}
}
