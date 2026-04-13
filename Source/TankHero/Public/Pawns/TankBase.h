// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBase.generated.h"

class USphereComponent;
class UCapsuleComponent;
class ATHPlayerController;
class UFloatingPawnMovement;
class ATHProjectile;

UCLASS()
class TANKHERO_API ATankBase : public APawn
{
	GENERATED_BODY()

public:
	ATankBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Attack")
	TSubclassOf<ATHProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Sounds")
	TObjectPtr<USoundBase> FireSound;

private:
	

};
