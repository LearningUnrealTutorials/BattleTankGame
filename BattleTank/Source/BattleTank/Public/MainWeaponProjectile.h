// by Aleksander Naumenok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainWeaponProjectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API AMainWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
private: //Variables
	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UStaticMeshComponent *CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UParticleSystemComponent *LaunchBlast = nullptr;

public:	//Variables

protected: //Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: //Functions
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);
	AMainWeaponProjectile(); // Sets default values for this actor's properties
};
