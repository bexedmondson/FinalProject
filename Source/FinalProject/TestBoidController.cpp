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

	if (boidCount == Super::GetNumberOfBoids())
	{
		return "TestBoidController: TestGenerateCorrectNumberOfBoids: pass.";
	}
	else
	{
		return "TestBoidController: TestGenerateCorrectNumberOfBoids: fail.";
	}
}