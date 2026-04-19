// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LevelItem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULevelItem::Initialize(int32 Index)
{
	Level->SetText(FText::AsNumber(Index));
	if (Index != 1)
	{
		Button->SetIsEnabled(false);
	}
}