// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestBoidController.h"

ATestBoidController::ATestBoidController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ATestBoidController::BeginPlay()
{

}

// Called every frame
void ATestBoidController::Tick(float DeltaTime)
{
	
}

FString ATestBoidController::TestGenerateCorrectNumberOfBoids()
{
	Super::GenerateBoids();

	int boidCount = 0;

	for (TActorIterator<ABoid> Itr(GetWorld()); Itr; ++Itr)
	{
		boidCount++;
	}

	Super::EmptyBoidArray();

	if (boidCount == Super::GetNumberOfBoids())
	{
		return "TestBoidController: TestGenerateCorrectNumberOfBoids: pass.";
	}
	else
	{
		FString errorMessage = "TestBoidController: TestGenerateCorrectNumberOfBoids: fail.\n";
		errorMessage += "Expected value: " + FString::FromInt(Super::GetNumberOfBoids()) + "\n";
		errorMessage += "Actual value:   " + FString::FromInt(boidCount);
		return errorMessage;
	}
}

FString ATestBoidController::TestGenerateBoidsOnlyInBox()
{
	Super::GenerateBoids();
	bool boidsInBox = true;
	FVector boidOutOfBoxLocation;

	FBox spawnBox = FBox(FVector(-Super::GetSpawnCubeSize()), FVector(Super::GetSpawnCubeSize()));

	for (TActorIterator<ABoid> Itr(GetWorld()); Itr; ++Itr)
	{
		if (!spawnBox.IsInsideOrOn(Itr->GetActorLocation()))
		{
			boidsInBox = false;
			boidOutOfBoxLocation = Itr->GetActorLocation();
			break;
		}
	}

	if (boidsInBox)
	{
		return "TestBoidController: TestGenerateBoidsOnlyInBox: pass.";
	}
	else
	{
		FString errorMessage = "TestBoidController: TestGenerateBoidsOnlyInBox: fail.\n";
		errorMessage += "Box max: " + spawnBox.Max.ToCompactString() + " Box min: " + spawnBox.Min.ToCompactString() + "\n";
		errorMessage += "Boid found: " + boidOutOfBoxLocation.ToCompactString();
		return errorMessage;
	}
}
