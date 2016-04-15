// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Boid.h"
#include "AIController.h"
#include "BoidController.generated.h"


/**
*
*/
UCLASS()
class FINALPROJECT_API ABoidController : public AAIController
{
	GENERATED_BODY()

public:
	ABoidController(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void SetControllerTarget(FVector target);

protected:
	UWorld* World;

	void GenerateBoids();

	FVector boidTarget;

	//test functions
	TArray<ABoid*> GetBoidArray();
	int GetNumberOfBoids();
	int GetSpawnCubeSize();
};
