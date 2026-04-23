// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Types/THTypes.h"
#include "THHUD.generated.h"

class ATHGameMode;

/**
 *
 */

UCLASS()
class TANKHERO_API ATHHUD : public AHUD
{
	GENERATED_BODY()

public:
	void SetLevelTime(float Time) { LevelTime = Time; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PauseWidget;

	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	TSubclassOf<UUserWidget> WinWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> WinWidget;

	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	TSubclassOf<UUserWidget> LoseWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> LoseWidget;

	UPROPERTY(EditDefaultsOnly, Category = "TH|UI")
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> OverlayWidget;

private:
	TWeakObjectPtr<ATHGameMode> THGameMode;

	UFUNCTION()
	void HandleStateChanged(EGamePlayState NewState);

	UFUNCTION()
	void HandleLevelEnd(float Time);

	UFUNCTION()
	void HandleLastLevel();

	void ShowWidget(TObjectPtr<UUserWidget>& Instance, TSubclassOf<UUserWidget> Class);

	UFUNCTION()
	void RequestPause();

	float LevelTime = 0.f;

	bool bLastLevel = false;
};