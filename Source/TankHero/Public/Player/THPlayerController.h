// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "THPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ATankPlayer;

/**
 * 
 */
UCLASS()
class TANKHERO_API ATHPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void PlayerTick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TH|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TH|Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& Value);

private:
	TWeakObjectPtr<ATankPlayer> Player;

	FVector CurrentMoveInput;
	FVector MouseWorldLocation;
};
