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
class UNiagaraSystem;

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

	UPROPERTY(EditAnywhere, Category = "TH|Weapon")
	TSubclassOf<ATHProjectile> NormalProjectileClass;

	UPROPERTY(EditAnywhere, Category = "TH|Weapon")
	TSubclassOf<ATHProjectile> SonicProjectileClass;

	UPROPERTY(EditAnywhere, Category = "TH|Weapon")
	TObjectPtr<UNiagaraSystem> LaserEffect;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Sounds")
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Sounds")
	TObjectPtr<USoundBase> LaserSound;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float Speed = 800.f;

private:
	

};
