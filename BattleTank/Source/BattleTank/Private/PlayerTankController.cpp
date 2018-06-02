// by Aleksander Naumenok
#include "PlayerTankController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();
	m_AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(m_AimingComponent)) return;
	FoundAimingComponent(m_AimingComponent);
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void APlayerTankController::AimTowardsCrosshair()
{
	if (!ensure(m_AimingComponent)) return;
	//Out parameter
	FVector HitLocation; 
	if (GetSightRayHitLocation(HitLocation))
	{
		m_AimingComponent->AimAt(HitLocation);
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
