// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthBarWidgetComponent.h"
#include "Pawns/TankBase.h"
#include "UI/HealthBar.h"

UHealthBarWidgetComponent::UHealthBarWidgetComponent()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
	SetVisibility(false);
}

void UHealthBarWidgetComponent::UpdateHealth(float Health, float MaxHealth)
{
    float Percent = Health / MaxHealth;
    SetVisibility(true);

    UHealthBar* HealthWidget = Cast<UHealthBar>(GetUserWidgetObject());
    if (HealthWidget)
    {
        HealthWidget->SetHealth(Percent);
    }

    GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &UHealthBarWidgetComponent::HideWidget, DisplayDuration, false);
}

void UHealthBarWidgetComponent::HideWidget()
{
    SetVisibility(false);
}
