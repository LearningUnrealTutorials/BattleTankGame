// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "MainWeaponProjectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them. GameplayStatics.h
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(const FVector &LocationToAimAt) const
{
	if (!ensure(Barrel && Turret)) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSpawnLocation"));
	//Calculate launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity (
		this, 
		OutLaunchVelocity, 
		StartLocation, 
		LocationToAimAt, 
		LaunchVelocity,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found!"), GetWorld()->GetTimeSeconds());
		MoveBarrelTowards(AimDirection);
		RotateTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::FireMainWeapon()
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


void UTankAimingComponent::MoveBarrelTowards(FVector &AimDirection) const
{
	Barrel->Elevate((AimDirection.Rotation() - Barrel->GetForwardVector().Rotation()).Pitch);
}

void UTankAimingComponent::RotateTurretTowards(FVector &AimDirection) const
{
	Turret->Rotate((AimDirection.Rotation() - Barrel->GetForwardVector().Rotation()).Yaw);
}

