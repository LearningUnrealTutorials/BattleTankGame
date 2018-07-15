// by Aleksander Naumenok

#include "Tank.h"
#include "UObjectGlobals.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Starts blueprint begin play
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, CurrentHealth);
	CurrentHealth -= damageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return damagePoints;
}

float ATank::GetHealthPercent()
{
	return (float) CurrentHealth / (float) StartingHealth;
}
