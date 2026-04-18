// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBar::SetHealth(float Percent)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(Percent);
        float ColorAlpha = FMath::GetMappedRangeValueClamped(FVector2D(0.2f, 0.8f), FVector2D(0.0f, 1.0f), Percent);
        FLinearColor CurrentColor = FMath::Lerp(LowHealthColor, FullHealthColor, ColorAlpha);
        HealthBar->SetFillColorAndOpacity(CurrentColor);
    }
}
