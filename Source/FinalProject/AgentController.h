// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Agent.h"
#include "AIController.h"
#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAgentController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAgentController(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:
	UWorld* World;

	void GenerateAgents();
	int CalculateZValue(int x, int y);

	void FindGlobalBest();
	FVector globalBest;
};
