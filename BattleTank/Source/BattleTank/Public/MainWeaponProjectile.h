// by Aleksander Naumenok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainWeaponProjectile.generated.h"

class UProjectileMovementComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AMainWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
private: //Variables

	void OnLifeTimerExpire();
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float DestroyDelay = 3.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ProjectileDamage = 10.f;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent *ExplosionForce = nullptr;

	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;

public:	//Variables

protected: //Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: //Functions
	// Called every frame
	void LaunchProjectile(float Speed);
	AMainWeaponProjectile(); // Sets default values for this actor's properties
};
