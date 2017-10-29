// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

//Forward declarations
class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
//Methods
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack* SetLeftTrack, UTankTrack* SetRightTrack);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendRotateRight(float Throw);
private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

//Variables
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
