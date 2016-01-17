// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		FVector currentVelocity;

	/** Boid new movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		FVector newVelocity;

	/** Boid rotation component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		FRotator rotation;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FVector CalculateBoidVelocity();

	void SetVelocity(FVector velocity);

	FVector GetVelocity();


protected:
	UStaticMeshComponent* BoidMesh;

	FVector SeparateBoid(std::vector<FVector> nearbyBoidLocations);
	FVector AlignBoid(std::vector<FRotator> nearbyBoidRotations);
	FVector CohereBoid(std::vector<FVector> nearbyBoidLocations);

};
