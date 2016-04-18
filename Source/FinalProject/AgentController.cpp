// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AgentController.h"
#include "Agent.h"

// constants for this file
static const int NUMBER_OF_AGENTS = 40; //number of agents to be spawned
static const int SPAWN_SQUARE_SIZE = 5000; //length of side of agent spawn square DIVIDED BY TWO

TArray<AAgent*> agentArray;

AAgentController::AAgentController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AAgentController::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	agentArray.Empty();
	GenerateAgents();

	globalBest = FVector(0, 0, -100000);
}

// Called every frame
void AAgentController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindGlobalBest();

	for (AAgent* agent : agentArray)
	{
		//update PSO variable
		agent->SetGlobalBest(globalBest);

		//respawn agents as appropriate
		if (agent->ShouldAgentBeRepawned())
		{
			agent->Destroy();
			agentArray.Remove(agent);
			agentArray.Add(SpawnNewAgent());
		}
	}
}


void AAgentController::GenerateAgents()
{
	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
		//add agent to array for agent algorithm calculations
		agentArray.Add(SpawnNewAgent());
	}
}

AAgent* AAgentController::SpawnNewAgent()
{
	FVector agentLocation = FVector();
	FRotator agentRotation = FRotator();

	//generate random numbers for location
	int randNumX = rand() % (SPAWN_SQUARE_SIZE - -SPAWN_SQUARE_SIZE + 1) + -SPAWN_SQUARE_SIZE;
	int randNumY = rand() % (SPAWN_SQUARE_SIZE - -SPAWN_SQUARE_SIZE + 1) + -SPAWN_SQUARE_SIZE;

	//randomise spawn point and rotation
	agentLocation = FVector(randNumX, randNumY, 0);
	agentRotation = FRotator::ZeroRotator;

	//spawn agent and return
	return GetWorld()->SpawnActor<AAgent>(AAgent::StaticClass(), agentLocation, agentRotation);
}

void AAgentController::FindGlobalBest()
{
	for (AAgent* agent : agentArray)
	{
		FVector agentBest = agent->GetAgentBest();
		if (agentBest.Z > globalBest.Z)
		{
			globalBest = agentBest;
		}
	}
}

// test function
TArray<AAgent*> AAgentController::GetAgentArray()
{
	return agentArray;
}

// test function
void AAgentController::EmptyAgentArray()
{
	agentArray.Empty();
}

// test function
int AAgentController::GetNumberOfAgents()
{
	return NUMBER_OF_AGENTS;
}

// test function
int AAgentController::GetSpawnSquareSize()
{
	return SPAWN_SQUARE_SIZE;
}

// test function
void AAgentController::AddAgentToArray(AAgent* agent)
{
	agentArray.Add(agent);
}

// test function
void AAgentController::RemoveAgentFromArray(AAgent* agent)
{
	agentArray.Remove(agent);
}

// test function
FVector AAgentController::GetGlobalBest()
{
	return globalBest;
}
