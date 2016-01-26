// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "BoidController.h"
#include "Boid.h"

// constants for this file
static const int NUMBER_OF_BOIDS = 30; //number of boids to be spawned
static const int SPAWN_CUBE_SIZE = 200; //length of side of boid spawn cube DIVIDED BY TWO

ABoidController::ABoidController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ABoidController::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	boidArray[NUMBER_OF_BOIDS] = {};

	GenerateBoids();

}


// Called every frame
void ABoidController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < NUMBER_OF_BOIDS; i++)
	{
		//set goal point
	}
}


void ABoidController::GenerateBoids() {

	FVector boidLocation = FVector();
	FRotator boidRotation = FRotator();

	for (int i = 0; i < NUMBER_OF_BOIDS; i++)
	{
		//generate random numbers for location
		int randNumX = rand() % (SPAWN_CUBE_SIZE - -SPAWN_CUBE_SIZE + 1) + -SPAWN_CUBE_SIZE;
		int randNumY = rand() % (SPAWN_CUBE_SIZE - -SPAWN_CUBE_SIZE + 1) + -SPAWN_CUBE_SIZE;
		int randNumZ = rand() % (SPAWN_CUBE_SIZE - -SPAWN_CUBE_SIZE + 1) + -SPAWN_CUBE_SIZE;

		//randomise spawn point and rotation
		boidLocation = FVector(randNumX, randNumY, randNumZ);
		boidRotation = FRotator(FMath::RandRange(-90, 90), FMath::RandRange(-180, 180), FMath::RandRange(-180, 180));

		//spawn boid
		ABoid* boid = GetWorld()->SpawnActor<ABoid>(ABoid::StaticClass(), boidLocation, boidRotation);

		//add boid to array for boid algorithm calculations
		boidArray[i] = boid;

	}
}

