// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declaration
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent;
class AMainWeaponProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

	//Local barrel referrence
	UTankBarrel *Barrel = nullptr; //TODO Remove

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	void AimAt(const FVector HitLocation) const;

	UFUNCTION(BlueprintCallable, Category = "Input")
		void FireMainWeapon();
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchVelocity = 10000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AMainWeaponProjectile> ProjectileBlueprint;

};
