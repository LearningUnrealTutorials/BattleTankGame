// Fill out your copyright notice in the Description page of Project Settings.

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

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret *TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::FireMainWeapon()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && isReloaded)
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