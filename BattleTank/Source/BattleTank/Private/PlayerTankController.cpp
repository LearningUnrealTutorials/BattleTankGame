// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerTankController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

ATank* APlayerTankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();
	UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	FoundAimingComponent(AimingComponent);
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void APlayerTankController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;
	//Out parameter
	FVector HitLocation; 
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool APlayerTankController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	///Raycast throug the dot
	///Put location into out parameter
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that Lookdirection
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

bool APlayerTankController::GetLookDirection(const FVector2D & ScreenLocation, FVector & OutLookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

bool APlayerTankController::GetLookVectorHitLocation(const FVector & LookDirection, FVector & OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}
