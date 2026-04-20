// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "THGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API UTHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void SetCurrentLevel(int32 NewLevel) { CurrentLevel = NewLevel; }
	int32 GetCurrentLevel() const { return CurrentLevel; }

protected:


private:
	int32 CurrentLevel = 0;
};
