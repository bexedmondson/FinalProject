// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Boid.h"

// Sets default values
ABoid::ABoid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// static mesh for visualisation
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Meshes/paperplane1_0.paperplane1_0'"));
	if (CubeMeshAsset.Succeeded())
	{
		PrimaryActorTick.bCanEverTick = true;
		BoidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoidMesh"));
		BoidMesh->SetStaticMesh(CubeMeshAsset.Object);
		RootComponent = BoidMesh;
		SetActorEnableCollision(true);
	}

	// attach sphere for detecting nearby boids
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->AttachTo(RootComponent);
	SphereComponent->InitSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("BoidCollider");
}

// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();

	// scale to be more easily visible
	SetActorScale3D(FVector(15, 15, 15));

	//initialise velocity
	currentVelocity = FVector(FMath::RandRange(-5.0f, 5.0f), FMath::RandRange(-5.0f, 5.0f), FMath::RandRange(-5.0f, 5.0f));

	//initialise rotation
	rotation = FRotator(0.0, 0.0, 0.0);

}

// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector totalVelocity = currentVelocity + newVelocity;

	rotation = totalVelocity.Rotation();

	SetActorLocationAndRotation(GetActorLocation() + totalVelocity, rotation);

	currentVelocity = totalVelocity;
}

void ABoid::SetVelocity(FVector velocity) {
	newVelocity = velocity;
}

FVector ABoid::CalculateBoidVelocity()
{
	TArray<UPrimitiveComponent*> nearbyComponents;
	GetOverlappingComponents(nearbyComponents);

	std::vector<FVector> nearbyBoidLocations = {};
	std::vector<FRotator> nearbyBoidRotations = {};

	// iterate over components to find only the boids
	for (int i = 0; i < nearbyComponents.Num(); i++)
	{
		UPrimitiveComponent* collidingComponent = nearbyComponents[i];
		AActor* colliderOwner = collidingComponent->GetOwner();

		if (colliderOwner->IsA(ABoid::StaticClass()))
		{
			FRotator colliderOwnerRotation = colliderOwner->GetActorRotation();
			nearbyBoidRotations.push_back(colliderOwnerRotation);

			FVector colliderOwnerLocation = colliderOwner->GetActorLocation();
			nearbyBoidLocations.push_back(colliderOwnerLocation);
		}
	}

	FVector separation = SeparateBoid(nearbyBoidLocations);
	FVector alignment = AlignBoid(nearbyBoidRotations);
	FVector cohesion = CohereBoid(nearbyBoidLocations);

	return ((separation * 1) + (alignment * 3) + (cohesion * 1)) * 0.05;
}

FVector ABoid::SeparateBoid(std::vector<FVector> nearbyBoidLocations)
{
	FVector separationSteer = FVector(0, 0, 0);
	FVector actorLocation = GetActorLocation();

	for (int i = 0; i < nearbyBoidLocations.size(); i++) {
		FVector nbLocation = nearbyBoidLocations[i];

		if (actorLocation != nbLocation)
		{
			//current location - other location because steering away from other location
			FVector diff = actorLocation - nbLocation;

			separationSteer += diff;
		}
	}

	//average out the steer
	return separationSteer / nearbyBoidLocations.size();
}

FVector ABoid::AlignBoid(std::vector<FRotator> nearbyBoidRotations)
{
	FRotator alignmentSteer = FRotator(0, 0, 0);
	FRotator actorRotation = GetActorRotation();

	for (int i = 0; i < nearbyBoidRotations.size(); i++) {
		FRotator nbRotation = nearbyBoidRotations[i];

		FRotator diff = nbRotation - actorRotation;
		alignmentSteer += diff;
	}

	//average out the alignment
	return alignmentSteer.Vector() / nearbyBoidRotations.size();
}

FVector ABoid::CohereBoid(std::vector<FVector> nearbyBoidLocations)
{
	FVector totalLocations = FVector(0, 0, 0);
	FVector cohesionSteer = FVector(0, 0, 0);
	FVector actorLocation = GetActorLocation();

	for (int i = 0; i < nearbyBoidLocations.size(); i++) {
		FVector nbLocation = nearbyBoidLocations[i];

		if (actorLocation != nbLocation)
		{
			totalLocations += nbLocation;
		}
	}

	//average out the total and get the direction this boid should be steering in
	cohesionSteer = (totalLocations / nearbyBoidLocations.size()) - actorLocation;

	return cohesionSteer;
}

