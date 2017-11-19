// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

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

private:
	void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Naviagation")
		float AcceptanceRadius = 50.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
