// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelItem.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TANKHERO_API ULevelItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(int32 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Level;

};
