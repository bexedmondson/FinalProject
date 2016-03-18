// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AgentController.h"
#include "Agent.h"

// constants for this file
static const int NUMBER_OF_AGENTS = 30; //number of agents to be spawned
static const int SPAWN_SQUARE_SIZE = 200; //length of side of agent spawn square DIVIDED BY TWO

AAgent* agentArray[NUMBER_OF_AGENTS] = {};

AAgentController::AAgentController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AAgentController::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	GenerateAgents();

	globalBest = FVector(0, 0, -100000);
}

// Called every frame
void AAgentController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindGlobalBest();

	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
		agentArray[i]->SetGlobalBest(globalBest);
	}
}


void AAgentController::GenerateAgents()
{

	FVector agentLocation = FVector();
	FRotator agentRotation = FRotator();

	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
		//generate random numbers for location
		int randNumX = rand() % (SPAWN_SQUARE_SIZE - -SPAWN_SQUARE_SIZE + 1) + -SPAWN_SQUARE_SIZE;
		int randNumY = rand() % (SPAWN_SQUARE_SIZE - -SPAWN_SQUARE_SIZE + 1) + -SPAWN_SQUARE_SIZE;
		int calculatedZ = CalculateZValue(randNumX, randNumY);

		//randomise spawn point and rotation
		agentLocation = FVector(randNumX, randNumY, calculatedZ);
		agentRotation = FRotator(FMath::RandRange(-90, 90), FMath::RandRange(-180, 180), FMath::RandRange(-180, 180));

		//spawn boid
		AAgent* agent = GetWorld()->SpawnActor<AAgent>(AAgent::StaticClass(), agentLocation, agentRotation);

		//add boid to array for boid algorithm calculations
		agentArray[i] = agent;
	}
}

int AAgentController::CalculateZValue(int x, int y) 
{
	return 0;
}

void AAgentController::FindGlobalBest()
{
	for (int i = 0; i < NUMBER_OF_AGENTS; i++)
	{
		FVector agentBest = agentArray[i]->GetAgentBest();
		if (agentBest.Z > globalBest.Z)
		{
			globalBest = agentBest;
		}
	}
}

