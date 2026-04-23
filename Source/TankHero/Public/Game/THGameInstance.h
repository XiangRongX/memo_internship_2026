// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "THGameInstance.generated.h"

UENUM(BlueprintType)
enum class EMusicState : uint8 
{ 
	Menu, 
	Level, 
	Win, 
	Lose,
	None
};

/**
 * 
 */
UCLASS()
class TANKHERO_API UTHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void SetCurrentLevel(int32 NewLevel) { CurrentLevel = NewLevel; }
	int32 GetCurrentLevel() const { return CurrentLevel; }
	void SetMaxLevel(int32 NewMaxLevel);
	int32 GetMaxLevel() const { return MaxLevel; }
	void SetSoundEnabled(bool bEnabled);
	void SetMusicEnabled(bool bEnabled);
	bool IsSoundEnabled() const { return bSoundEnabled; }
	bool IsMusicEnabled() const { return bMusicEnabled; }
	void SetFollowEnabled(bool bEnabled) { bFollowEnabled = bEnabled; }
	bool IsFollowEnabled() const { return bFollowEnabled; }
	void SetVibrateEnabled(bool bEnabled) { bVibrateEnabled = bEnabled; }
	bool IsVibrateEnabled() const { return bVibrateEnabled; }

	UFUNCTION(BlueprintCallable)
	void SwitchMusicState(EMusicState NewState);

protected:
	UPROPERTY(EditAnywhere, Category = "TH|Audio")
	TObjectPtr<USoundMix> GlobalSoundMix;

	UPROPERTY(EditAnywhere, Category = "TH|Audio")
	TObjectPtr<USoundClass> MusicClass;

	UPROPERTY(EditAnywhere, Category = "TH|Audio")
	TObjectPtr<USoundClass> SoundClass;

	UPROPERTY(EditAnywhere, Category = "TH|Audio")
	TObjectPtr<USoundBase> MenuMusic;

	UPROPERTY(EditAnywhere, Category = "TH|Audio")
	TArray<TObjectPtr<USoundBase>> LevelMusicList;

	UPROPERTY(EditAnywhere, Category = "TH|Audio")
	TObjectPtr<USoundBase> WinMusic;

	UPROPERTY(EditAnywhere, Category = "TH|Audio")
	TObjectPtr<USoundBase> LoseMusic; 

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> BGMComponent;

private:
	int32 CurrentLevel = 0;
	int32 MaxLevel = 1;

	bool bSoundEnabled = true;
	bool bMusicEnabled = true;
	bool bFollowEnabled = true;
	bool bVibrateEnabled = true;
};
