// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponPickup.h"
#include "Pawns/TankPlayer.h"

void AWeaponPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATankPlayer* Player = Cast<ATankPlayer>(OtherActor))
	{
		Player->SwitchWeapon(WeaponType);
	}

	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
