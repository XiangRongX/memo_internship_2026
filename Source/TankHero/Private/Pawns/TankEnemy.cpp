// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ATankEnemy::ATankEnemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATankEnemy::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    AAIController* AIC = Cast<AAIController>(NewController);
    if (AIC)
    {
        AIC->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
        AIC->RunBehaviorTree(BehaviorTree);
        
    }
}