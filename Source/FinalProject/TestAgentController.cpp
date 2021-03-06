// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestAgentController.h"

ATestAgentController::ATestAgentController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ATestAgentController::BeginPlay()
{

}

// Called every frame
void ATestAgentController::Tick(float DeltaTime)
{

}

FString ATestAgentController::TestGenerateCorrectNumberOfAgents()
{
	// also tests SpawnNewAgent

	Super::GenerateAgents();

	int agentCount = 0;

	for (TActorIterator<AAgent> Itr(GetWorld()); Itr; ++Itr)
	{
		agentCount++;
	}

	Super::EmptyAgentArray();

	if (agentCount == Super::GetNumberOfAgents())
	{
		return "TestAgentController: TestGenerateCorrectNumberOfAgents: pass.";
	}
	else
	{
		FString errorMessage = "TestAgentController: TestGenerateCorrectNumberOfAgents: fail.\n";
		errorMessage += "Expected value: " + FString::FromInt(Super::GetNumberOfAgents()) + "\n";
		errorMessage += "Actual value:   " + FString::FromInt(agentCount);
		return errorMessage;
	}
}

FString ATestAgentController::TestGenerateAgentsOnlyInBox()
{
	// also tests SpawnNewAgent

	Super::GenerateAgents();
	bool agentsInBox = true;
	FVector agentOutOfBoxLocation;

	FBox spawnBox = FBox(FVector(-Super::GetSpawnSquareSize()), FVector(Super::GetSpawnSquareSize()));

	for (TActorIterator<AAgent> Itr(GetWorld()); Itr; ++Itr)
	{
		if (!spawnBox.IsInsideOrOn(Itr->GetActorLocation()))
		{
			agentsInBox = false;
			agentOutOfBoxLocation = Itr->GetActorLocation();
			break;
		}
	}

	if (agentsInBox)
	{
		return "ATestAgentController: TestGenerateAgentsOnlyInBox: pass.";
	}
	else
	{
		FString errorMessage = "ATestAgentController: TestGenerateAgentsOnlyInBox: fail.\n";
		errorMessage += "Box max: " + spawnBox.Max.ToCompactString() + " Box min: " + spawnBox.Min.ToCompactString() + "\n";
		errorMessage += "Agent found: " + agentOutOfBoxLocation.ToCompactString();
		return errorMessage;
	}
}

FString ATestAgentController::TestFindGlobalBest()
{
	AAgent* testAgent = Super::SpawnNewAgent();
	testAgent->SetActorLocation(FVector(0, 0, 100000));
	testAgent->CheckAgentBest();
	Super::AddAgentToArray(testAgent);

	Super::FindGlobalBest();

	Super::RemoveAgentFromArray(testAgent);
	testAgent->Destroy();

	if (Super::GetGlobalBest().Equals(FVector(0, 0, 100000), 2.5))
	{
		return "ATestAgentController: TestFindGlobalBest: pass.";
	}
	else
	{
		FString errorMessage = "ATestAgentController: TestFindGlobalBest: fail.\n";
		errorMessage += "Expected value: " + FVector(0, 0, 100000).ToCompactString() + "\n";
		errorMessage += "Actual value:   " + Super::GetGlobalBest().ToCompactString() + "\n";
		return errorMessage;
	}
}
