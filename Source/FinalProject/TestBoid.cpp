// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestBoid.h"

ATestBoid::ATestBoid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ATestBoid::BeginPlay()
{

}

// Called every frame
void ATestBoid::Tick(float DeltaTime)
{

}

FString ATestBoid::TestCalculateVelocityInBoxAndAlone()
{
	Super::SetTarget(FVector::ZeroVector);

	FVector calculatedVelocity = Super::CalculateBoidVelocity();

	if (calculatedVelocity.Equals(FVector::ZeroVector, 2))
	{
		return "TestBoid: TestCalculateVelocityInBoxAndAlone: pass.";
	}
	else
	{
		FString errorMessage = "TestBoid: TestCalculateVelocityInBoxAndAlone: fail.\n";
		errorMessage += "Expected value: " + FVector::ZeroVector.ToCompactString() + "\n";
		errorMessage += "Actual value:   " + calculatedVelocity.ToCompactString();
		return errorMessage;
	}
}

FString ATestBoid::TestCalculateVelocityOutOfBoxAndAlone()
{
	Super::SetTarget(FVector(10000, 10000, 10000));

	FVector calculatedVelocity = Super::CalculateBoidVelocity();

	if (calculatedVelocity.Equals(FVector(50, 50, 50), 2))
	{
		return "TestBoid: TestCalculateVelocityOutOfBoxAndAlone: pass.";
	}
	else
	{
		FString errorMessage = "TestBoid: TestCalculateVelocityOutOfBoxAndAlone: fail.\n";
		errorMessage += "Expected value: " + FVector(50, 50, 50).ToCompactString() + "\n";
		errorMessage += "Actual value:   " + calculatedVelocity.ToCompactString();
		return errorMessage;
	}
}
