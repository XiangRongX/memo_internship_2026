// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/THGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

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

void UTHGameInstance::SwitchMusicState(EMusicState NewState)
{
    if (NewState == EMusicState::None)
    {
        if (BGMComponent && BGMComponent->IsPlaying())
        {
            BGMComponent->SetPaused(true);
        }
        return;
    }

    USoundBase* TargetSound = nullptr;
    switch (NewState)
    {
    case EMusicState::Menu:
        TargetSound = MenuMusic;
        break;
    case EMusicState::Level:
        if (BGMComponent && LevelMusicList.Contains(BGMComponent->Sound))
        {
            TargetSound = BGMComponent->Sound;
        }
        else if (LevelMusicList.Num() > 0)
        {
            int32 Index = FMath::RandRange(0, LevelMusicList.Num() - 1);
            TargetSound = LevelMusicList[Index];
        }
        break;
    case EMusicState::Win:
        TargetSound = WinMusic;
        break;
    case EMusicState::Lose:
        TargetSound = LoseMusic;
        break;
    }

    if (!TargetSound) return;

    if (!BGMComponent)
    {
        BGMComponent = UGameplayStatics::CreateSound2D(this, TargetSound, 1.0f, 1.0f, 0.0f, nullptr, false, false);
        if (BGMComponent)
        {
            BGMComponent->bAutoDestroy = false;
            BGMComponent->bIsUISound = true;
        }
    }

    if (BGMComponent)
    {
        if (BGMComponent->Sound == TargetSound && BGMComponent->bIsPaused)
        {
            if (IsMusicEnabled())
            {
                BGMComponent->SetPaused(false);
            }
            return;
        }

        if (BGMComponent->IsPlaying() && BGMComponent->Sound != TargetSound)
        {
            BGMComponent->FadeOut(0.5f, 0.0f);
        }
        else if (BGMComponent->Sound == TargetSound && BGMComponent->IsPlaying())
        {
            return;
        }

        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, TargetSound]()
            {
                if (BGMComponent)
                {
                    BGMComponent->SetSound(TargetSound);
                    BGMComponent->SetPaused(false);

                    if (IsMusicEnabled())
                    {
                        BGMComponent->FadeIn(0.f);
                    }
                    else
                    {
                        BGMComponent->Play();
                        BGMComponent->SetVolumeMultiplier(0.0f);
                    }
                }
            }, 0.5f, false);
    }
}
