// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "UObjectGlobals.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "MainWeaponProjectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Starts blue print begin play
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	Barrel = FindComponentByClass<UTankBarrel>();
}

void ATank::AimAt(const FVector HitLocation) const
{
	if (!ensure(TankAimingComponent)) return;
	TankAimingComponent->AimAt(HitLocation);
}


void ATank::FireMainWeapon()
{
	if (!ensure(Barrel)) return;
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded)
	{
		//Fire main weapon by spawning projectile at the end of the barrel
		AMainWeaponProjectile *ProjectileClone = GetWorld()->SpawnActor<AMainWeaponProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("ProjectileSpawnLocation")),
				Barrel->GetSocketRotation(FName("ProjectileSpawnLocation"))
			);
		ProjectileClone->LaunchProjectile(LaunchVelocity);
		LastFireTime = FPlatformTime::Seconds();
	}
}