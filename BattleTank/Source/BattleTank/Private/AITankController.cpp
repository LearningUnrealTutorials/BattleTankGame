// Fill out your copyright notice in the Description page of Project Settings.
#include "AITankController.h"
#include "Tank.h"
#include "Engine/World.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if(ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->FireMainWeapon(); //TODO Not fire every time
	}
}
