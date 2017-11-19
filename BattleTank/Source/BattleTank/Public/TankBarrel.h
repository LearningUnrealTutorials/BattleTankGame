// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds information and methods related to barrel
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 8.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 18.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = -3.0f;
};
