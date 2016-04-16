// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Boid.generated.h"

#define FloorChannel ECC_Pawn

UCLASS()
class FINALPROJECT_API ABoid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoid(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// for goalseeking
	void SetTarget(FVector boidTarget);

	FVector CalculateBoidVelocity();

protected:
	UStaticMeshComponent* BoidMesh;

	// boid current movement component
	FVector currentVelocity;

	// boid rotation component
	FRotator rotation;

	// corner of bounding box, set by BoidController
	FVector boundingBoxCorner;

	// functions to calculate main components of boids algorithm
	FVector SeparateBoid(TArray<FVector> nearbyBoidLocations);
	FVector AlignBoid(TArray<FRotator> nearbyBoidRotations);
	FVector CohereBoid(TArray<FVector> nearbyBoidLocations);

	// additions to main boids algorithm to keep flock contained and to enable goalseeking
	FVector KeepBoidInBox();
};
