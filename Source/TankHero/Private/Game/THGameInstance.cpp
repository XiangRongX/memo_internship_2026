// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/THGameInstance.h"

void UTHGameInstance::SetMaxLevel(int32 NewMaxLevel)
{
	if (NewMaxLevel > MaxLevel)
	{
		MaxLevel = NewMaxLevel;
	}
}
