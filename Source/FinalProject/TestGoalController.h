// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GoalController.h"
#include "TestGoalController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ATestGoalController : public AGoalController
{
	GENERATED_BODY()

public:
	ATestGoalController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FString TestFindsAllGoalsAtStart();
	FString TestCalculateScores();
};
