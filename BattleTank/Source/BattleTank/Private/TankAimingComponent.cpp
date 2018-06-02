// by Aleksander Naumenok

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
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	///Begin game by reloading main weapon
	LastFireTime = FPlatformTime::Seconds();
	FiringState = EFiringState::Reloading;
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (Barrel == nullptr) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(m_AimDirection, 0.1f);
}

void UTankAimingComponent::AimAt(const FVector &LocationToAimAt)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSpawnLocation"));
	//Calculate launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity 
	(
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
		m_AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found!"), GetWorld()->GetTimeSeconds());
		MoveBarrelTowards(m_AimDirection);
		RotateTurretTowards(m_AimDirection);
	}
}

void UTankAimingComponent::FireMainWeapon()
{
	
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		//Fire main weapon by spawning projectile at the end of the barrel
		AMainWeaponProjectile *ProjectileClone = GetWorld()->SpawnActor<AMainWeaponProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("ProjectileSpawnLocation")),
				Barrel->GetSocketRotation(FName("ProjectileSpawnLocation"))
				);
		ProjectileClone->LaunchProjectile(LaunchVelocity);
		FiringState = EFiringState::Reloading;
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

