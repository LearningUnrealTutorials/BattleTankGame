// by Aleksander Naumenok

#include "SpringWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);
	Mass->SetNotifyRigidBodyCollision(true);
	Mass->SetVisibility(true);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Mass); //AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->SetVisibility(true);

	//WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	//WheelConstraint->SetupAttachment(Mass); //AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//WheelConstraint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

