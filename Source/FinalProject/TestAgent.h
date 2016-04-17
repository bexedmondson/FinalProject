// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Agent.h"
#include "TestAgent.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ATestAgent : public AAgent
{
	GENERATED_BODY()

public:
	ATestAgent(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;	
	
	FString TestCheckAgentBest();
	
};
