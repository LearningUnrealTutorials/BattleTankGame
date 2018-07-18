// by Aleksander Naumenok

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

//Forward declaration
class UTankAimingComponent;

/**
 * Handlesp player input
 */
UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);
public: 
	// Called every frame
	void Tick(float DeltaTime) override;
private:
	//Move tank barrel towards crosshair
	UTankAimingComponent* m_AimingComponent;
	void AimTowardsCrosshair();
	bool SetupAimingComponent();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookDirection(const FVector2D &ScreenLocation, FVector & OutLookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
		void OnPossessedTankDeath();
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;
};
