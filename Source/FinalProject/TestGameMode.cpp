// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestGameMode.h"
#include "TestBoidController.h"
#include "TestBoid.h"
#include "TestAgentController.h"
#include "TestAgent.h"
#include "TestGoalController.h"
#include "TestGoal.h"
#include "InputController.h"
#include "CoreMisc.h"
#include "Paths.h"
#include "DateTime.h"

ATestBoidController* testBoidControllerPtr = NULL;
ATestAgentController* testAgentControllerPtr = NULL;
ATestGoalController* testGoalControllerPtr = NULL;
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
	testAgentControllerPtr = GetWorld()->SpawnActor<ATestAgentController>(ATestAgentController::StaticClass());
	testGoalControllerPtr = GetWorld()->SpawnActor<ATestGoalController>(ATestGoalController::StaticClass());

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
	FString testFileNameString = FPaths::GameDir();
	testFileNameString += "TestResults.log";
	const TCHAR* testFileName = *testFileNameString;

	FString testResultString = FDateTime::Now().ToString() + "\n";

	testResultString += RunBoidControllerTests() + "\n";
	testResultString += RunBoidTests() + "\n";
	testResultString += RunAgentControllerTests() + "\n";
	testResultString += RunAgentTests() + "\n";
	testResultString += RunGoalControllerTests() + "\n";
	testResultString += RunGoalTests() + "\n";

	FFileHelper::SaveStringToFile(testResultString, testFileName);

	if (testResultString.Contains("fail"))
	{
		//CHANGE THIS TO SOMETHING ON HUD
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Test failed, check TestResults.log for details.");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "All tests passed.");
	}
}

FString ATestGameMode::RunBoidControllerTests()
{
	FString boidControllerTestResultString = "";

	boidControllerTestResultString += testBoidControllerPtr->TestGenerateCorrectNumberOfBoids() + "\n";
	boidControllerTestResultString += testBoidControllerPtr->TestGenerateBoidsOnlyInBox() + "\n";
	
	return boidControllerTestResultString;
}

FString ATestGameMode::RunBoidTests()
{
	FString boidTestResultString = "";

	//spawn test boid
	ATestBoid* testBoid = GetWorld()->SpawnActor<ATestBoid>(ATestBoid::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

	boidTestResultString += testBoid->TestCalculateVelocityInBoxAndAlone() + "\n";
	boidTestResultString += testBoid->TestCalculateVelocityOutOfBoxAndAlone() + "\n";
	boidTestResultString += testBoid->TestCalculateVelocityInBoxAndOneInOuterSphere() + "\n";
	boidTestResultString += testBoid->TestCalculateVelocityInBoxAndOneInInnerSphere() + "\n";

	testBoid->Destroy();

	return boidTestResultString;
}

FString ATestGameMode::RunAgentControllerTests()
{
	FString agentControllerTestResultString = "";

	agentControllerTestResultString += testAgentControllerPtr->TestGenerateCorrectNumberOfAgents() + "\n";
	agentControllerTestResultString += testAgentControllerPtr->TestGenerateAgentsOnlyInBox() + "\n";
	agentControllerTestResultString += testAgentControllerPtr->TestFindGlobalBest() + "\n";

	return agentControllerTestResultString;
}

FString ATestGameMode::RunAgentTests()
{
	FString agentTestResultString = "";

	//spawn test agent
	ATestAgent* testAgent = GetWorld()->SpawnActor<ATestAgent>(ATestAgent::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

	agentTestResultString += testAgent->TestCheckAgentBest() + "\n";

	testAgent->Destroy();

	return agentTestResultString;
}

FString ATestGameMode::RunGoalControllerTests()
{
	FString goalControllerTestResultString = "";

	goalControllerTestResultString += testGoalControllerPtr->TestFindsAllGoalsAtStart() + "\n";
	goalControllerTestResultString += testGoalControllerPtr->TestCalculateScores() + "\n";

	return goalControllerTestResultString;
}

FString ATestGameMode::RunGoalTests()
{
	FString goalTestResultString = "";

	//get test goal
	ATestGoal* testGoal = GetWorld()->SpawnActor<ATestGoal>(ATestGoal::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

	goalTestResultString += testGoal->TestTeamChangeToPlayer() + "\n";
	goalTestResultString += testGoal->TestTeamChangeToEnemy() + "\n";

	testGoal->Destroy();

	return goalTestResultString;
}
