// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "GoalController.h"
#include "Goal.h"

TArray<AGoal*> goalArray;

// Sets default values
AGoalController::AGoalController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoalController::BeginPlay()
{
	Super::BeginPlay();

	goalArray.Empty();

	for (TActorIterator<AGoal> Itr(GetWorld()); Itr; ++Itr)
	{
		goalArray.Add(*Itr);
	}
}

// Called every frame
void AGoalController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	CalculateScores();
}

void AGoalController::CalculateScores()
{
	int playerGoalCount = 0;
	int neutralGoalCount = 0;
	int enemyGoalCount = 0;

	for (AGoal* goal : goalArray)
	{
		Team goalTeam = goal->GetTeam();
		if (goalTeam == Team::PLAYER)
		{
			playerGoalCount++;
		}
		else if (goalTeam == Team::ENEMY)
		{
			enemyGoalCount++;
		}
		else
		{
			neutralGoalCount++;
		}
	}

	PlayerGoalScore = playerGoalCount;
	NeutralGoalScore = neutralGoalCount;
	EnemyGoalScore = enemyGoalCount;
}

