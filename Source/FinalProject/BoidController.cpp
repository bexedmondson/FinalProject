// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "BoidController.h"
#include "Boid.h"

ABoidController::ABoidController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ABoidController::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	numOfBoids = 40;
	boidArray[numOfBoids] = {};

	GenerateBoids();

}


// Called every frame
void ABoidController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < numOfBoids; i++)
	{
		//set goal point
	}
}


void ABoidController::GenerateBoids() {

	FVector boidLocation = FVector();
	FRotator boidRotation = FRotator();

	for (int i = 0; i < numOfBoids; i++)
	{
		//generate random numbers for location
		int randNumX = rand() % (200 - -200 + 1) + -200;
		int randNumY = rand() % (200 - -200 + 1) + -200;
		int randNumZ = rand() % (200 - -200 + 1) + -200;

		//randomise spawn point and rotation
		boidLocation = FVector(randNumX, randNumY, randNumZ);
		boidRotation = FRotator(FMath::RandRange(-90, 90), FMath::RandRange(-180, 180), FMath::RandRange(-180, 180));

		//spawn boid
		ABoid* boid = GetWorld()->SpawnActor<ABoid>(ABoid::StaticClass(), boidLocation, boidRotation);

		//add boid to array for boid algorithm calculations
		boidArray[i] = boid;

	}
}

