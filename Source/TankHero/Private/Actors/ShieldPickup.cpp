// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ShieldPickup.h"
#include "Pawns/TankPlayer.h"

void AShieldPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATankPlayer* Player = Cast<ATankPlayer>(OtherActor))
	{
		Player->ActivateShield(Duration);
	}

	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}