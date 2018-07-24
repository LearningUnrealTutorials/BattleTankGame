// by Aleksander Naumenok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

//forward declaration
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Suspension")
		UStaticMeshComponent *Mass = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Suspension")
		UStaticMeshComponent *Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Suspension")
		UPhysicsConstraintComponent *WheelConstraint = nullptr;

	
	
};
