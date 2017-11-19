// Fill out your copyright notice in the Description page of Project Settings.
#include "AITankController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();


	if(ensure(PlayerTank) && ensure(ControlledTank))
	{
		UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->FireMainWeapon(); //TODO Not fire every time
	}
}
