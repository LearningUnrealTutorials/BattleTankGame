// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainWeaponProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AMainWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;

public:	
	// Sets default values for this actor's properties
	AMainWeaponProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);
};
