// by Aleksander Naumenok

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
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



public: //Variables
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchVelocity = 10000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AMainWeaponProjectile> ProjectileBlueprint;

public: //Functions
	void AimAt(const FVector &LocationToAimAt);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void FireMainWeapon();
	UFUNCTION(BlueprintCallable, Category = "Firing")
		EFiringState GetFiringState() const;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetAmmoCount() const;

protected: //Variables
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

private: //Variables
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	FVector m_AimDirection;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	int m_AmmoCount = 3;

private: //Functions
	void MoveBarrelTowards(FVector &AimDirection) const;
	void RotateTurretTowards(FVector &AimDirection) const;
	// Sets default values for this component's properties
	UTankAimingComponent();
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void BeginPlay() override;
	bool IsBarrelMoving() const;
};
