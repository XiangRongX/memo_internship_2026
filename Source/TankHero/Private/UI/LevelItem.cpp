// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LevelItem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Game/THGameInstance.h"

void ULevelItem::Init(int32 Index)
{
	LevelIndex = Index;
	Level->SetText(FText::AsNumber(Index));
	if (Index != 1)
	{
		Button->SetIsEnabled(false);
	}
}

void ULevelItem::SetEnabled(bool bEnabled)
{
	if(Button)
	{
		Button->SetIsEnabled(bEnabled);
	}
}

void ULevelItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked);
	}
}

void ULevelItem::OnButtonClicked()
{
	if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
	{
		THGameInstance->SetCurrentLevel(LevelIndex);
	}

	FString LevelName = FString::Printf(TEXT("Level%d"), LevelIndex);
	UGameplayStatics::OpenLevel(this, FName(*LevelName));
}