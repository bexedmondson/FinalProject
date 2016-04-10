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

}

