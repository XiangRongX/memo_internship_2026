// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelMenu.generated.h"

class UUniformGridPanel;
class ULevelItem;

/**
 * 
 */
UCLASS()
class TANKHERO_API ULevelMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void ConstructLevelGrid(int32 TotalLevels);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> LevelGrid;

    UPROPERTY(EditAnywhere, Category = "TH|UI")
    TSubclassOf<ULevelItem> LevelItemClass;

    UPROPERTY(EditAnywhere, Category = "TH|UI")
    int32 Columns = 5;

};
