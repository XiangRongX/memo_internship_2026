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
class ASonicProjectile;
class UHealthBarWidgetComponent;

UCLASS()
class TANKHERO_API ATankBase : public APawn
{
	GENERATED_BODY()

public:
	ATankBase();
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	float GetDamage() const { return Damage; }

protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath();

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UHealthBarWidgetComponent> HealthBarWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "TH|Weapon")
	TSubclassOf<ATHProjectile> NormalProjectileClass;

	UPROPERTY(EditAnywhere, Category = "TH|Weapon")
	TSubclassOf<ASonicProjectile> SonicProjectileClass;

	UPROPERTY(EditAnywhere, Category = "TH|Weapon")
	TObjectPtr<UNiagaraSystem> LaserEffect;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Sounds")
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Sounds")
	TObjectPtr<USoundBase> LaserSound;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Sounds")
	TObjectPtr<USoundBase> SonicSound;

	UPROPERTY(EditAnywhere, Category = "TH|Settings")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = "TH|Settings")
	float Health;

	UPROPERTY(EditAnywhere, Category = "TH|Settings")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float Speed = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Animation")
	TObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Effects")
	TObjectPtr<UNiagaraSystem> DeathEffect;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Effects")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

private:
	

};
