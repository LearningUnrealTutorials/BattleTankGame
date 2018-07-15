// by Aleksander Naumenok

#include "AITankController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn != nullptr)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if(!ensure(PossessedTank))
		{ return; }

		//Subscrie to tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AAITankController::OnPossessedTankDeath);
	}
}

void AAITankController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }

	UE_LOG(LogTemp, Warning, TEXT("Tank has died"));
	GetPawn()->DetachFromControllerPendingDestroy();
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();


	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
		UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if(AimingComponent->GetFiringState() == EFiringState::Locked)
			AimingComponent->FireMainWeapon();
}
