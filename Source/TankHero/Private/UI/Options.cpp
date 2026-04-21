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
