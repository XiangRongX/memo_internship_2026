// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/THAnimInstance.h"
#include "Pawns/TankPlayer.h"

void UTHAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ATankPlayer* Player = Cast<ATankPlayer>(TryGetPawnOwner());
	if (!Player) return;

	TurretRotation = Player->GetTurretRelativeRotation();
	bIsMoving = Player->GetVelocity().Size() > 10.f;
}
