// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerWall.generated.h"

class UBoxComponent;

UCLASS()
class TANKHERO_API ATriggerWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ATriggerWall();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "TH|TriggerWall")
	void TriggerLowering();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TH|Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "TH|Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditDefaultsOnly, Category = "TH|Settings")
	float ResetDelay = 3.0f;

	UFUNCTION(BlueprintImplementableEvent, Category = "TH|TriggerWall")
	void ResetWall();

private:	
	FVector OriginalLocation;
	FTimerHandle ResetTimerHandle;
	bool bIsLowered = false;

	void TryResetWall();

};
