// by Aleksander Naumenok

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"


/**
 * Handles input from AI
 */
UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()

private: //Functions
	void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
		void OnPossessedTankDeath();

public: //Functions
	virtual void Tick(float DeltaTime) override;
	
protected: //variables
	UPROPERTY(EditDefaultsOnly, Category = "Naviagation")
		float AcceptanceRadius = 200.0f;
};
