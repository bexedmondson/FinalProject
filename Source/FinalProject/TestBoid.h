// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Boid.h"
#include "TestBoid.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ATestBoid : public ABoid
{
	GENERATED_BODY()

public:
	ATestBoid(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	FString TestCalculateVelocityInBoxAndAlone();
	FString TestCalculateVelocityOutOfBoxAndAlone();
	FString TestCalculateVelocityInBoxAndOneInOuterSphere();
	FString TestCalculateVelocityInBoxAndOneInInnerSphere();

	void ResetBoid();
};
