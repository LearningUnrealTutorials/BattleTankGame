// Written in 2017 by Aleksander Naumenok while following a tutorial on udemy.

#include "Tank.h"
#include "UObjectGlobals.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Starts blue print begin play
}