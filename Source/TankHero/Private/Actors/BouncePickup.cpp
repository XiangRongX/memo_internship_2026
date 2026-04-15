// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BouncePickup.h"
#include "Pawns/TankPlayer.h"

void ABouncePickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATankPlayer* Player = Cast<ATankPlayer>(OtherActor))
	{
		Player->IncreaseBounce(BounceToIncrease);
	}

	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}