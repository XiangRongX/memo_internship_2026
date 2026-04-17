// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FacePlayer.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API UBTTask_FacePlayer : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
public:
	UBTTask_FacePlayer();

	UPROPERTY(EditAnywhere, Category = "AI")
	float Precision = 5.0f;
};
