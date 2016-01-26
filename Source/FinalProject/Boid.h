// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Boid.generated.h"

UCLASS()
class FINALPROJECT_API ABoid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoid(const FObjectInitializer& ObjectInitializer);


	/** Boid current movement component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		FVector currentVelocity;

	/** Boid new movement component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		FVector newVelocity;

	/** Boid rotation component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		FRotator rotation;

	// Corner of bounding box, set by BoidController
	FVector boundingBoxCorner;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FVector CalculateBoidVelocity();

	void SetVelocity(FVector velocity);


protected:
	UStaticMeshComponent* BoidMesh;

	FVector SeparateBoid(TArray<FVector> nearbyBoidLocations);
	FVector AlignBoid(TArray<FRotator> nearbyBoidRotations);
	FVector CohereBoid(TArray<FVector> nearbyBoidLocations);

	FVector KeepBoidInBox();
};
