// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidgetComponent.generated.h"

class ATankBase;
class UHealthBar;

/**
 * 
 */
UCLASS()
class TANKHERO_API UHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UHealthBarWidgetComponent();

	void UpdateHealth(float Health, float MaxHealth);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	float DisplayDuration = 3.0f;

private:
	FTimerHandle HideTimerHandle;
	void HideWidget();
};
