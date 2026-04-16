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

	FRotator GetTurretRelativeRotation() const { return TurretRelativeRotation; }
	FName GetTankName() const { return TankName; }

protected:
	virtual void PossessedBy(AController* NewController) override;

	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	EWeaponType CurrentWeaponType = EWeaponType::Normal;

	UPROPERTY(EditDefaultsOnly, Category = "TH|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	FName TankName;

private:
	FRotator TurretRelativeRotation;

};
