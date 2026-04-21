// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Options.h"
#include "Components/CheckBox.h"
#include "Game/THGameInstance.h"

void UOptions::NativeConstruct()
{
	Super::NativeConstruct();

    if (UTHGameInstance* GameInstance = Cast<UTHGameInstance>(GetGameInstance()))
    {
        if (CheckBox_Music) CheckBox_Music->SetIsChecked(GameInstance->IsMusicEnabled());
        if (CheckBox_Sound) CheckBox_Sound->SetIsChecked(GameInstance->IsSoundEnabled());
        if (CheckBox_Follow) CheckBox_Follow->SetIsChecked(GameInstance->IsFollowEnabled());
        if (CheckBox_Vibrate) CheckBox_Vibrate->SetIsChecked(GameInstance->IsVibrateEnabled());
    }
}

void UOptions::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (CheckBox_Sound)
    {
        CheckBox_Sound->OnCheckStateChanged.AddDynamic(this, &UOptions::OnSoundCheckBoxChanged);
    }
    if (CheckBox_Music)
    {
        CheckBox_Music->OnCheckStateChanged.AddDynamic(this, &UOptions::OnMusicCheckBoxChanged);
	}
    if (CheckBox_Follow)
    {
        CheckBox_Follow->OnCheckStateChanged.AddDynamic(this, &UOptions::OnFollowCheckBoxChanged);
    }
    if (CheckBox_Vibrate)
    {
        CheckBox_Vibrate->OnCheckStateChanged.AddDynamic(this, &UOptions::OnVibrateCheckBoxChanged);
    }
}

void UOptions::OnSoundCheckBoxChanged(bool bIsChecked)
{
    if (UTHGameInstance* GameInstance = Cast<UTHGameInstance>(GetGameInstance()))
    {
		GameInstance->SetSoundEnabled(bIsChecked);
    }
}

void UOptions::OnMusicCheckBoxChanged(bool bIsChecked)
{
    if (UTHGameInstance* GameInstance = Cast<UTHGameInstance>(GetGameInstance()))
    {
        GameInstance->SetMusicEnabled(bIsChecked);
	}
}

void UOptions::OnFollowCheckBoxChanged(bool bIsChecked)
{
    if (UTHGameInstance* GameInstance = Cast<UTHGameInstance>(GetGameInstance()))
    {
        GameInstance->SetFollowEnabled(bIsChecked);
    }
}

void UOptions::OnVibrateCheckBoxChanged(bool bIsChecked)
{
    if (UTHGameInstance* GameInstance = Cast<UTHGameInstance>(GetGameInstance()))
    {
        GameInstance->SetVibrateEnabled(bIsChecked);
    }
}
