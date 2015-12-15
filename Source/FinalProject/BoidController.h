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

	//number of boids to be spawned
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	int numOfBoids;

protected:
	UWorld* World;

	ABoid* boidArray[];

	void GenerateBoids();
};
