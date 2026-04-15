// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class TANKHERO_API ATHProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATHProjectile();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	void AddToBounce(int32 BounceToAdd);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Components")
	TObjectPtr<UNiagaraComponent> ProjectileEffect;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float Speed = 800.f;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	int32 MaxBounces = 3;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Effects")
	TObjectPtr<UNiagaraSystem> DestroyEffect;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	int32 CurrentBounces = 0;

};
