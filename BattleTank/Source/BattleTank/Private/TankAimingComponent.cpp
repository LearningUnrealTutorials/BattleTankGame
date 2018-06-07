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

//Handle reloading and firing states
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_AmmoCount <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
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
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
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
		m_AmmoCount--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetAmmoCount() const
{
	return m_AmmoCount;
}

void UTankAimingComponent::MoveBarrelTowards(FVector &AimDirection) const
{
	Barrel->Elevate((AimDirection.Rotation() - Barrel->GetForwardVector().Rotation()).Pitch);
}

void UTankAimingComponent::RotateTurretTowards(FVector &AimDirection) const
{
	FRotator DeltaRotator = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		//Turret->Rotate((AimDirection.Rotation() - Barrel->GetForwardVector().Rotation()).Yaw);
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

}

