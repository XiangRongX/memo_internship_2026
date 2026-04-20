// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting.h"
#include "UI/Options.h"
#include "Components/Button.h"

void USetting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_Return)
	{
		Button_Return->OnClicked.AddDynamic(this, &ThisClass::OnReturnButtonClicked);
	}
}

void USetting::OnReturnButtonClicked()
{
	OnReturnClicked.Broadcast();
}