// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestGameMode.h"
#include "TestBoidController.h"
#include "Boid.h"
#include "AgentController.h"
#include "InputController.h"
#include "GoalController.h"

ATestBoidController* testBoidControllerPtr = NULL;
int frameCount;

ATestGameMode::ATestGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AInputController::StaticClass();
}

void ATestGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();
	frameCount = 0;

	testBoidControllerPtr = GetWorld()->SpawnActor<ATestBoidController>(ATestBoidController::StaticClass());
	AAgentController* agentControllerPtr = GetWorld()->SpawnActor<AAgentController>(AAgentController::StaticClass());
	AGoalController* goalControllerPtr = GetWorld()->SpawnActor<AGoalController>(AGoalController::StaticClass());

	inputControllerPtr->SetBoidControllerPtr(testBoidControllerPtr);
}

APlayerController* ATestGameMode::SpawnPlayerController(ENetRole RemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
	APlayerController* pc = Super::SpawnPlayerController(RemoteRole, SpawnLocation, SpawnRotation);

	//cast to inputcontroller
	inputControllerPtr = Cast<AInputController>(pc);
	return pc;
}

void ATestGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//run some tests shortly after level has loaded, but only run once
	bool haveTenthFrameTestsRun = false;

	if (!haveTenthFrameTestsRun && frameCount > 10) {
		RunTests();
		haveTenthFrameTestsRun = true;
	}

	if (haveTenthFrameTestsRun)
	{
		UGameplayStatics::OpenLevel(this, "Main");
	}

	frameCount++;
}

void ATestGameMode::RunTests()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, testBoidControllerPtr->TestGenerateCorrectNumberOfBoids());

	//if (allStrings.Contains("fail")
	//	print message? idk do something
}
