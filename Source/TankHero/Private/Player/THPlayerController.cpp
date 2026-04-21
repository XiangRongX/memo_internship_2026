// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/THPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Pawns/TankPlayer.h"
#include "Actors/THCameraManager.h"

void ATHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	bShowMouseCursor = true;
}

void ATHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATHPlayerController::Move);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATHPlayerController::OnLeftClick);
	}
}

void ATHPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Player = Cast<ATankPlayer>(InPawn);
}

void ATHPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!Player.IsValid()) return;
	if (!bCanRotate) return;

	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		MouseWorldLocation = HitResult.ImpactPoint;
		Player->UpdateTurretTarget(MouseWorldLocation);
	}

	Player->UpdateChassisTargetVector(CurrentMoveInput);
	CurrentMoveInput = FVector::ZeroVector;
}

void ATHPlayerController::Move(const FInputActionValue& Value)
{
	if (!Player.IsValid()) return;

	FVector2D MovementVector = Value.Get<FVector2D>();
	CurrentMoveInput = FVector(MovementVector.Y, MovementVector.X, 0.f);

	if (!CurrentMoveInput.IsNearlyZero())
	{
		CurrentMoveInput.Normalize();
		Player->AddMovementInput(CurrentMoveInput, 1.0f);
	}

}

void ATHPlayerController::OnLeftClick()
{
	if (!Player.IsValid()) return;

	Player->Fire();
}
