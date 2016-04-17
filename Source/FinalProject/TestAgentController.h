// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AgentController.h"
#include "TestAgentController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ATestAgentController : public AAgentController
{
	GENERATED_BODY()

public:
	ATestAgentController(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	FString TestGenerateCorrectNumberOfAgents();
	FString TestGenerateAgentsOnlyInBox();
};
