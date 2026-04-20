// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelMenu.generated.h"

class UUniformGridPanel;
class ULevelItem;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelMenuButtonClicked);

/**
 * 
 */
UCLASS()
class TANKHERO_API ULevelMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void ConstructLevelGrid(int32 TotalLevels);
	
    FOnLevelMenuButtonClicked OnReturnClicked;

protected:
    virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Button_Return;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> LevelGrid;

    UPROPERTY(EditAnywhere, Category = "TH|UI")
    TSubclassOf<ULevelItem> LevelItemClass;

    UPROPERTY(EditAnywhere, Category = "TH|UI")
    int32 Columns = 5;

private:
    UFUNCTION()
	void OnReturnButtonClicked();

	TArray<TObjectPtr<ULevelItem>> LevelItems;

    UFUNCTION()
    void SetLevelItemEnabled(int32 LevelIndex);
};
