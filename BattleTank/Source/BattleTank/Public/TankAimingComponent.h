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
class AMainWeaponProjectile;

//Holds barrel properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private: //Variables
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

public: //Variables
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchVelocity = 10000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AMainWeaponProjectile> ProjectileBlueprint;

protected: 
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

public: //Functions
	void AimAt(const FVector &LocationToAimAt) const;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void FireMainWeapon();

private: //Functions
	void MoveBarrelTowards(FVector &AimDirection) const;
	void RotateTurretTowards(FVector &AimDirection) const;
	// Sets default values for this component's properties
	UTankAimingComponent();
};
