// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/TankBase.h"
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

	void Fire();

	void UpdateChassisTargetVector(FVector MoveVector) { TargetChassisVector = MoveVector; }
	void UpdateTurretTarget(FVector MouseLocation) { TargetTurretLocation = MouseLocation; }
	FRotator GetTurretRelativeRotation() const { return TurretRelativeRotation; }

protected:
	virtual void BeginPlay() override;

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

private:
	TWeakObjectPtr<ATHPlayerController> PlayerController;

	FVector TargetChassisVector;
	FVector TargetTurretLocation;
	FRotator TurretRelativeRotation;
};
