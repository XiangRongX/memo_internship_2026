// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LevelMenu.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Button.h"
#include "UI/LevelItem.h"
#include "Game/THGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULevelMenu::NativeConstruct()
{
	Super::NativeConstruct();

    ConstructLevelGrid(15);
}

void ULevelMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    if (Button_Return)
    {
		Button_Return->OnClicked.AddDynamic(this, &ThisClass::OnReturnButtonClicked);
    }
}

void ULevelMenu::ConstructLevelGrid(int32 TotalLevels)
{
    if (!LevelGrid || !LevelItemClass) return;

    LevelGrid->ClearChildren();

    for (int32 i = 0; i < TotalLevels; ++i)
    {
        ULevelItem* NewItem = CreateWidget<ULevelItem>(this, LevelItemClass);
        if (NewItem)
        {
            NewItem->Init(i + 1);

            UUniformGridSlot* GridSlot = LevelGrid->AddChildToUniformGrid(NewItem);
            int32 Row = i / Columns;
            int32 Col = i % Columns;
            GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
            GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
            GridSlot->SetRow(Row);
            GridSlot->SetColumn(Col);
        }
		LevelItems.Add(NewItem);
    }

    if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(UGameplayStatics::GetGameInstance(this)))
    {
        int32 MaxLevel = THGameInstance->GetMaxLevel();
        for (int32 i = 0; i < MaxLevel; i++)
        {
            SetLevelItemEnabled(i + 1);
        }
    }
}

void ULevelMenu::SetLevelItemEnabled(int32 LevelIndex)
{
    if (LevelItems.IsValidIndex(LevelIndex - 1))
    {
        LevelItems[LevelIndex - 1]->SetEnabled(true);
	}
}

void ULevelMenu::OnReturnButtonClicked()
{
	OnReturnClicked.Broadcast();
}