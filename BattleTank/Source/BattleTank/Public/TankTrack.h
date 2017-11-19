// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Handles tank tracks
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	///Maximum force per track in newtons, assume that tank weight is 40 tonne and 1g acceleration
	UPROPERTY(EditDefaultsOnly, Category = "Locomotion")
		float TrackMaxDrivingForce = 400000;
};
