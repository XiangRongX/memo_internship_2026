// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetRandomLocation.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    APawn* Pawn = AIC->GetPawn();
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

    if (NavSys && Pawn)
    {
        FNavLocation RandomLoc;
        if (NavSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), 1500.f, RandomLoc))
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("WanderLocation"), RandomLoc.Location);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}
