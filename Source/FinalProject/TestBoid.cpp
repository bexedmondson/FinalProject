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
	// testing constant velocity given no other effects

	Super::SetTarget(FVector::ZeroVector);

	FVector calculatedVelocity = Super::CalculateBoidVelocity();

	ResetBoid();

	if (calculatedVelocity.Equals(FVector::ZeroVector, 3))
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
	// testing keepboidinbox

	Super::SetTarget(FVector(10000, 10000, 10000));

	FVector calculatedVelocity = Super::CalculateBoidVelocity();

	ResetBoid();

	if (calculatedVelocity.Equals(FVector(50, 50, 50), 3))
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

FString ATestBoid::TestCalculateVelocityInBoxAndOneInOuterSphere()
{
	// testing separate and align

	ATestBoid* directionBoid = GetWorld()->SpawnActor<ATestBoid>(ATestBoid::StaticClass(), FVector(15, 15, 15), FRotator::ZeroRotator);

	FVector calculatedVelocity = Super::CalculateBoidVelocity();

	directionBoid->Destroy();
	ResetBoid();

	if (calculatedVelocity.Equals(FVector(0.6, 0.6, 0.6), 3))
	{
		return "TestBoid: TestCalculateVelocityInBoxAndOneInOuterSphere: pass.";
	}
	else
	{
		FString errorMessage = "TestBoid: TestCalculateVelocityInBoxAndOneInOuterSphere: fail.\n";
		errorMessage += "Expected value: " + FVector(0.6, 0.6, 0.6).ToCompactString() + "\n";
		errorMessage += "Actual value:   " + calculatedVelocity.ToCompactString();
		return errorMessage;
	}
}

FString ATestBoid::TestCalculateVelocityInBoxAndOneInInnerSphere()
{
	// testing separate, align, cohere

	ATestBoid* directionBoid = GetWorld()->SpawnActor<ATestBoid>(ATestBoid::StaticClass(), FVector(5, 5, 5), FRotator::ZeroRotator);

	FVector calculatedVelocity = Super::CalculateBoidVelocity();

	directionBoid->Destroy();
	ResetBoid();

	if (calculatedVelocity.Equals(FVector(-0.2, -0.2, -0.2), 3))
	{
		return "TestBoid: TestCalculateVelocityInBoxAndOneInInnerSphere: pass.";
	}
	else
	{
		FString errorMessage = "TestBoid: TestCalculateVelocityInBoxAndOneInInnerSphere: fail.\n";
		errorMessage += "Expected value: " + FVector(0.6, 0.6, 0.6).ToCompactString() + "\n";
		errorMessage += "Actual value:   " + calculatedVelocity.ToCompactString();
		return errorMessage;
	}
}

void ATestBoid::ResetBoid()
{
	// utility function

	Super::SetCurrentVelocity(FVector::ZeroVector);
	Super::SetTarget(FVector::ZeroVector);
	Super::SetActorLocation(FVector::ZeroVector);
}
