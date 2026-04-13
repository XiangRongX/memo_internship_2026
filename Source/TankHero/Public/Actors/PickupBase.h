// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class USphereComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class TANKHERO_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UNiagaraComponent> Effect;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float RotationSpeed = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float FloatAmplitude = 8.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float FloatFrequency = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Effects")
	TObjectPtr<UNiagaraSystem> PickupEffect;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Sounds")
	TObjectPtr<USoundBase> PickupSound;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float RunningTime = 0.0f;
	FVector InitialVisualLocation;
};
