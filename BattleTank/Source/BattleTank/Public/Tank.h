// by Aleksander Naumenok

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent();
	FTankDelegate OnDeath;

private:
	UPROPERTY(EditAnywhere, Category = "Status")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Status")
		int32 CurrentHealth = 0;
};
