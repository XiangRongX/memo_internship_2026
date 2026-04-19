// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LevelMenu.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "UI/LevelItem.h"

void ULevelMenu::NativeConstruct()
{
	Super::NativeConstruct();

    ConstructLevelGrid(15);
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
            NewItem->Initialize(i + 1);

            UUniformGridSlot* GridSlot = LevelGrid->AddChildToUniformGrid(NewItem);
            int32 Row = i / Columns;
            int32 Col = i % Columns;
            GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
            GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
            GridSlot->SetRow(Row);
            GridSlot->SetColumn(Col);
        }
    }
}