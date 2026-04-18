// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class TANKHERO_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealth(float Percent);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(EditAnywhere, Category = "TH|UI")
	FLinearColor FullHealthColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, Category = "TH|UI")
	FLinearColor LowHealthColor = FLinearColor::Red;
};
