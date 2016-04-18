// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "TestGoalController.h"

ATestGoalController::ATestGoalController()
	: Super()
{

}

void ATestGoalController::BeginPlay()
{

}

// Called every frame
void ATestGoalController::Tick(float DeltaTime)
{

}

FString ATestGoalController::TestFindsAllGoalsAtStart()
{
	Super::BeginPlay();

	if (Super::GetGoalArray().Num() == 13)
	{
		return "TestGoalController: TestFindsAllGoalsAtStart: pass.";
	}
	else
	{
		FString errorMessage = "TestGoalController: TestFindsAllGoalsAtStart: fail.\n";
		errorMessage += "Expected value: 13\n";
		errorMessage += "Actual value:   " + FString::FromInt(Super::GetGoalArray().Num());
		return errorMessage;
	}
}

FString ATestGoalController::TestCalculateScores()
{
	TArray<AGoal*> goalArray = Super::GetGoalArray();

	for (int i = 0; i < goalArray.Num(); i++)
	{
		if (i < 3)
		{
			goalArray[i]->SetTeam(ETeam::PLAYER);
		}
		else if (i < 7)
		{
			goalArray[i]->SetTeam(ETeam::NEUTRAL);
		}
		else
		{
			goalArray[i]->SetTeam(ETeam::ENEMY);
		}
	}

	Super::CalculateScores();


	for (int i = 0; i < goalArray.Num(); i++)
	{
		goalArray[i]->SetTeam(ETeam::NEUTRAL);
	}

	if (Super::PlayerGoalScore == 3 && Super::NeutralGoalScore == 4 && Super::EnemyGoalScore == 6)
	{
		return "TestGoalController: TestCalculateScores: pass.";
	}
	else
	{
		FString errorMessage = "TestGoalController: TestCalculateScores: fail.\n";
		errorMessage += "Expected value: Player 3, Neutral 4, Enemy 6\n";
		errorMessage += "Actual value:   Player " + FString::FromInt(Super::PlayerGoalScore) + ", Neutral " + FString::FromInt(Super::NeutralGoalScore) + ", Enemy " + FString::FromInt(Super::EnemyGoalScore);
		return errorMessage;
	}
}
