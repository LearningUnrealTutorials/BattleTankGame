// Fill out your copyright notice in the Description page of Project Settings.
#include "AITankController.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController found player: %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController could not find player tank!"));
	}
}

ATank * AAITankController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* AAITankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
