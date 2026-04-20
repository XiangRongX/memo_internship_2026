// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LobbyGameMode.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController= UGameplayStatics::GetPlayerController(this, 0))
	{
		FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
}
