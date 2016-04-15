// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestGameMode.h"
#include "TestBoidController.h"
#include "Boid.h"
#include "AgentController.h"
#include "InputController.h"
#include "GoalController.h"

ATestGameMode::ATestGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AInputController::StaticClass();
}

void ATestGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	ATestBoidController* boidControllerPtr = GetWorld()->SpawnActor<ATestBoidController>(ATestBoidController::StaticClass());
	AAgentController* agentControllerPtr = GetWorld()->SpawnActor<AAgentController>(AAgentController::StaticClass());
	AGoalController* goalControllerPtr = GetWorld()->SpawnActor<AGoalController>(AGoalController::StaticClass());

	inputControllerPtr->SetBoidControllerPtr(boidControllerPtr);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "TESTING");
}

APlayerController* ATestGameMode::SpawnPlayerController(ENetRole RemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
	APlayerController* pc = Super::SpawnPlayerController(RemoteRole, SpawnLocation, SpawnRotation);

	//cast to inputcontroller
	inputControllerPtr = Cast<AInputController>(pc);
	return pc;
}


