// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/PickupBase.h"
#include "SpeedPickup.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API ASpeedPickup : public APickupBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float SpeedToAdd = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float Duration = 10.f;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
