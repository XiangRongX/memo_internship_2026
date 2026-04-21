// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THCameraActor.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TANKHERO_API ATHCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATHCameraActor();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere)
	float MoveLimit = 500.f;

	UPROPERTY(EditAnywhere)
	float MinArmLength = 1200.f;

	UPROPERTY(EditAnywhere)
	float MaxArmLength = 1500.f;	
};
