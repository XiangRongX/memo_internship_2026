// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Fire.h"
#include "Pawns/TankEnemy.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ATankEnemy* Enemy = Cast<ATankEnemy>(OwnerComp.GetAIOwner()->GetPawn());
    if (Enemy)
    {
        Enemy->Fire();
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
