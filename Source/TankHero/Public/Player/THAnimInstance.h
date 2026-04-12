// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "THAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TANKHERO_API UTHAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "TH|Animation")
	FRotator TurretRotation;

	UPROPERTY(BlueprintReadOnly, Category = "TH|Animation")
	bool bIsMoving;

private:


};
