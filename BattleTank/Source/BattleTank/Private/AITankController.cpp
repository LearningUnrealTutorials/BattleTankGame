// Fill out your copyright notice in the Description page of Project Settings.
#include "AITankController.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController possesing: %s"), *(GetControlledTank()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController not possesing a tank!"));
	}
}

ATank* AAITankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
