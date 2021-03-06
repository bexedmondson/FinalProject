// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestAgent.h"

ATestAgent::ATestAgent()
	: Super()
{

}

void ATestAgent::BeginPlay()
{

}

// Called every frame
void ATestAgent::Tick(float DeltaTime)
{

}

FString ATestAgent::TestCheckAgentBest()
{
	Super::SetActorLocation(FVector(0, 0, 10000));
	
	Super::CheckAgentBest();

	FVector agentBest = Super::GetAgentBest();

	if (agentBest.Equals(FVector(0, 0, 10000), 3))
	{
		return "TestAgent: TestCheckAgentBest: pass.";
	}
	else
	{
		FString errorMessage = "TestAgent: TestCheckAgentBest: fail.\n";
		errorMessage += "Expected value: " + FVector(0, 0, 10000).ToCompactString() + "\n";
		errorMessage += "Actual value:   " + agentBest.ToCompactString();
		return errorMessage;
	}
}

// testing aligntolandscape not possible, as spawning landscape from code is not possible

// testing calculateagentvelocity not possible, as random coefficient means exact test impossible
