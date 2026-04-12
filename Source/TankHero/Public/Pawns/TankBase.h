// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBase.generated.h"

class USphereComponent;
class UCapsuleComponent;
class ATHPlayerController;
class UFloatingPawnMovement;

UCLASS()
class TANKHERO_API ATankBase : public APawn
{
	GENERATED_BODY()

public:
	ATankBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "FH|Components")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "FH|Components")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere, Category = "FH|Components")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

private:
	

};
