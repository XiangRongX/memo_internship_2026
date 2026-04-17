// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FacePlayer.h"
#include "AI/THAIController.h"
#include "Pawns/TankEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FacePlayer::UBTTask_FacePlayer()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_FacePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTask_FacePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    ATHAIController* AIC = Cast<ATHAIController>(OwnerComp.GetAIOwner());
    ATankEnemy* Enemy = Cast<ATankEnemy>(AIC->GetPawn());
    AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor")));

    if (Enemy && Target)
    {
        FRotator CurrentTurretWorldRot = Enemy->GetActorRotation() + Enemy->GetTurretRelativeRotation();

        FVector Dir = (Target->GetActorLocation() - Enemy->GetActorLocation()).GetSafeNormal();
        FRotator LookAtRot = Dir.Rotation();

        float AngleDiff = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentTurretWorldRot.Yaw, LookAtRot.Yaw));

        if (AngleDiff <= Precision)
        {
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        }
    }
}
