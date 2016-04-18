// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Goal.h"
#include "TestGoal.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ATestGoal : public AGoal
{
	GENERATED_BODY()

public:
	ATestGoal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	FString TestTeamChangeToPlayer();
	FString TestTeamChangeToEnemy();

};
