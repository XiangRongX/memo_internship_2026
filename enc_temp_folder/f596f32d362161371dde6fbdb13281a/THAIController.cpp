// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/THAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Pawns/TankEnemy.h"

ATHAIController::ATHAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 1500.f; 
    SightConfig->LoseSightRadius = 1700.f;
    SightConfig->PeripheralVisionAngleDegrees = 90.f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
    AIPerceptionComponent->ConfigureSense(*SightConfig);
    AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ATHAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ATankEnemy* Enemy = Cast<ATankEnemy>(GetPawn());
    AActor* Target = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FName("TargetActor")));
    if (Enemy)
    {
        FVector MoveVec = Enemy->GetVelocity();
        if (!MoveVec.IsNearlyZero())
        {
            Enemy->UpdateChassisTargetVector(MoveVec.GetSafeNormal());
        }
        if (Target)
        {
            Enemy->UpdateTurretTarget(Target->GetActorLocation());
        }
    }
}

void ATHAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void ATHAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Actor->ActorHasTag(FName("Player")))
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            Blackboard->SetValueAsObject(FName("TargetActor"), Actor);
        }
        else
        {
            Blackboard->ClearValue(FName("TargetActor"));
        }
    }
}
