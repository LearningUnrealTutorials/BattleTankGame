// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

//Forward declaration
class ATank;
class UTankAimingComponent;

/**
 * Handlesp player input
 */
UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);
public: 
	// Called every frame
	void Tick(float DeltaTime) override;
private:
	//Move tank barrel towards crosshair
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookDirection(const FVector2D &ScreenLocation, FVector & OutLookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;
};
