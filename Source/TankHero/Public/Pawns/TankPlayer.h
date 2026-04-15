// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/TankBase.h"
#include "Types/THTypes.h"
#include "TankPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TANKHERO_API ATankPlayer : public ATankBase
{
	GENERATED_BODY()
	
public:
	ATankPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Fire();
	void ActivateShield(float Duration);
	void BoostSpeed(float SpeedToAdd, float Duration);
	void IncreaseBounce(int32 BounceToAdd);

	void UpdateChassisTargetVector(FVector MoveVector) { TargetChassisVector = MoveVector; }
	void UpdateTurretTarget(FVector MouseLocation) { TargetTurretLocation = MouseLocation; }
	FRotator GetTurretRelativeRotation() const { return TurretRelativeRotation; }
	void SwitchWeapon(EWeaponType NewType) { CurrentWeaponType = NewType; }

protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Movement")
	float ChassisRotateSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Movement")
	float TurretRotateSpeed = 15.f;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<USkeletalMeshComponent> LeftWheel;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<USkeletalMeshComponent> RightWheel;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float FireCooldown = 0.5f;

private:
	TWeakObjectPtr<ATHPlayerController> PlayerController;

	FVector TargetChassisVector;
	FVector TargetTurretLocation;
	FRotator TurretRelativeRotation;

	EWeaponType CurrentWeaponType = EWeaponType::Normal;
	void FireNormal();
	void FireDouble();
	void FireLaser();
	void FireSonic();

	FTimerHandle CooldownTimerHandle;
	bool bCanFire = true;
	void ResetFire() { bCanFire = true; }

	bool bIsShielded = false;
	FTimerHandle ShieldTimer;
	FTimerHandle SpeedTimer;
	void DeactivateShield();
	void ResetSpeed();

	int32 BounceToIncrease = 0;
};
