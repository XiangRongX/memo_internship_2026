// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "THAIController.generated.h"

class UBehaviorTreeComponent;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;
struct FAIStimulus;

/**
 * 
 */
UCLASS()
class TANKHERO_API ATHAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATHAIController();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY()
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
