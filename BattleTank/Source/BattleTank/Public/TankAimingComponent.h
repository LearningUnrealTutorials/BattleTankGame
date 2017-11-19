// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward declaration
class UTankBarrel; 
class UTankTurret;

//Holds barrel properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

public:	
	void AimAt(const FVector &LocationToAimAt, float LaunchVelocity = 5000.0f) const;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

private:
	void MoveBarrelTowards(FVector &AimDirection) const;
	void RotateTurretTowards(FVector &AimDirection) const;
	// Sets default values for this component's properties
	UTankAimingComponent();
};
