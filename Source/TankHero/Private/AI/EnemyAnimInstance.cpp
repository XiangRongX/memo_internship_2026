// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAnimInstance.h"
#include "Pawns/TankEnemy.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ATankEnemy* Enemy = Cast<ATankEnemy>(TryGetPawnOwner());
	if (!Enemy) return;

	TurretRotation = Enemy->GetTurretRelativeRotation();
	bIsMoving = Enemy->GetVelocity().Size() > 10.f;
	TankName = Enemy->GetTankName();
}