// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"


//Forward declaration
class ATank;

/**
 * Handles input from AI
 */
UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()

private:
	void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Naviagation)
		float AcceptanceRadius = 50.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
