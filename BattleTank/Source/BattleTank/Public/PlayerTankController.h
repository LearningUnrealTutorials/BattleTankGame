// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;

public: 
	// Called every frame
	void Tick(float DeltaTime) override;
private:
	ATank* GetControlledTank() const;
	//Move tank barrel towards crosshair
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookDirection(const FVector2D &ScreenLocation, FVector & OutLookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;
};
