// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestGoal.h"
#include "Boid.h"
#include "Agent.h"

ATestGoal::ATestGoal()
	: Super()
{

}

void ATestGoal::BeginPlay()
{

}

// Called every frame
void ATestGoal::Tick(float DeltaTime)
{

}

FString ATestGoal::TestTeamChangeToPlayer()
{
	Super::SetTeam(ETeam::NEUTRAL);

	TArray<ABoid*> boidArray;

	for (int i = 0; i < 12; i++)
	{
		boidArray.Add(GetWorld()->SpawnActor<ABoid>(ABoid::StaticClass(), FVector(5, 5, 5), FRotator::ZeroRotator));
	}

	Super::CheckForActorsInSphere();

	for (ABoid* boid : boidArray)
	{
		boid->Destroy();
	}

	boidArray.Empty();

	if (Super::GetTeam() == ETeam::PLAYER)
	{
		return "TestGoal: TestTeamChangeToPlayer: pass.";
	}
	else
	{
		FString errorMessage = "TestGoal: TestTeamChangeToPlayer: fail.\n";
		errorMessage += "Expected value: Player\n";
		
		if (Super::GetTeam() == ETeam::NEUTRAL)
		{
			errorMessage += "Actual value:   Neutral";
		}
		else
		{
			errorMessage += "Actual value:   Enemy";
		}
		return errorMessage;
	}
}

FString ATestGoal::TestTeamChangeToEnemy()
{
	Super::SetActorLocation(FVector(1000, 0, 0));
	Super::SetTeam(ETeam::NEUTRAL);

	TArray<AAgent*> agentArray;

	for (int i = 0; i < 3; i++)
	{
		agentArray.Add(GetWorld()->SpawnActor<AAgent>(AAgent::StaticClass(), FVector(1005, 0, 0), FRotator::ZeroRotator));
	}

	Super::CheckForActorsInSphere();

	for (AAgent* agent : agentArray)
	{
		agent->Destroy();
	}

	agentArray.Empty();

	if (Super::GetTeam() == ETeam::ENEMY)
	{
		return "TestGoal: TestTeamChangeToEnemy: pass.";
	}
	else
	{
		FString errorMessage = "TestGoal: TestTeamChangeToEnemy: fail.\n";
		errorMessage += "Expected value: Enemy\n";

		if (Super::GetTeam() == ETeam::NEUTRAL)
		{
			errorMessage += "Actual value:   Neutral";
		}
		else
		{
			errorMessage += "Actual value:   Player";
		}
		return errorMessage;
	}
}

