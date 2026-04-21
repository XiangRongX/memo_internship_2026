// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/THGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UTHGameInstance::SetMaxLevel(int32 NewMaxLevel)
{
	if (NewMaxLevel > MaxLevel)
	{
		MaxLevel = NewMaxLevel;
	}
}

void UTHGameInstance::SetSoundEnabled(bool bEnabled)
{
	bSoundEnabled = bEnabled;
	float NewVolume = bEnabled ? 1.0f : 0.0f;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), GlobalSoundMix, SoundClass, NewVolume, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), GlobalSoundMix);
}

void UTHGameInstance::SetMusicEnabled(bool bEnabled)
{
	bMusicEnabled = bEnabled;
	float NewVolume = bEnabled ? 1.0f : 0.0f;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), GlobalSoundMix, MusicClass, NewVolume, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), GlobalSoundMix);
}
