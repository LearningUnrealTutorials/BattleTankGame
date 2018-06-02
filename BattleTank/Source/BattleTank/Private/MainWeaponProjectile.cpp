// by Aleksander Naumenok

#include "MainWeaponProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMainWeaponProjectile::AMainWeaponProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AMainWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainWeaponProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

