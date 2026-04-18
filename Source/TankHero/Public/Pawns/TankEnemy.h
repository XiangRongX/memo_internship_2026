// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/TankBase.h"
#include "Types/THTypes.h"
#include "TankEnemy.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class TANKHERO_API ATankEnemy : public ATankBase
{
	GENERATED_BODY()
	
public:
	ATankEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Fire();

	void UpdateChassisTargetVector(FVector TargetVector) { TargetChassisVector = TargetVector; }
	void UpdateTurretTarget(FVector TargetLocation) { TargetTurretLocation = TargetLocation; }
	FRotator GetTurretRelativeRotation() const { return TurretRelativeRotation; }
	FName GetTankName() const { return TankName; }

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void HandleDeath() override;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Movement")
	float ChassisRotateSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Movement")
	float TurretRotateSpeed = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	EWeaponType CurrentWeaponType = EWeaponType::Normal;

	UPROPERTY(EditDefaultsOnly, Category = "TH|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	FName TankName;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Animation")
	TObjectPtr<UAnimMontage> HitMontage;

private:
	FVector TargetChassisVector;
	FVector TargetTurretLocation;
	FRotator TurretRelativeRotation;

	void FireNormal();
	void FireDouble();
	void FireLaser();
	void FireSonic();

};
