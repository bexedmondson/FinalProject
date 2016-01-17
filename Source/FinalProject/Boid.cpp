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
	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->SetCollisionProfileName("BoidCollider");
}

// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();

	// scale to be more easily visible
	SetActorScale3D(FVector(15, 15, 15));

	//initialise velocity
	//currentVelocity = FVector(FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(-0.5f, 0.5f));
	currentVelocity = FVector(0, 0, 0);

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

void ABoid::SetVelocity(FVector velocity) 
{
	newVelocity = velocity;
}

FVector ABoid::GetVelocity()
{
	return currentVelocity;
}

FVector ABoid::CalculateBoidVelocity()
{
	TArray<UPrimitiveComponent*> nearbyComponents;
	GetOverlappingComponents(nearbyComponents);
	
	std::vector<AActor *> nearbyBoids = {};
	std::vector<FVector> nearbyBoidLocations = {};
	std::vector<FRotator> nearbyBoidRotations = {};

	// iterate over components to find only the boids
	for (int i = 0; i < nearbyComponents.Num(); i++)
	{
		UPrimitiveComponent* collidingComponent = nearbyComponents[i];
		AActor* colliderOwner = collidingComponent->GetOwner();

		if (colliderOwner->IsA(ABoid::StaticClass()))
		{
			//if boid array doesn't already have the boid in it
			if (std::find(nearbyBoids.begin(), nearbyBoids.end(), colliderOwner) == nearbyBoids.end()) {
				nearbyBoids.push_back(colliderOwner);
			}
		}
	}

	FString numOfBoidsString = FString::FromInt(nearbyBoids.size());

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, numOfBoidsString);

	for (int i = 0; i < nearbyBoids.size(); i++) {
		FRotator colliderOwnerRotation = nearbyBoids[i]->GetActorRotation();
		nearbyBoidRotations.push_back(colliderOwnerRotation);

		FVector colliderOwnerLocation = nearbyBoids[i]->GetActorLocation();
		nearbyBoidLocations.push_back(colliderOwnerLocation);
	}

	try
	{
		FVector separation = SeparateBoid(nearbyBoidLocations);
		FVector alignment = AlignBoid(nearbyBoidRotations);
		FVector cohesion = CohereBoid(nearbyBoidLocations);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "NOT EMPTY");

		return ((separation * 1) + (alignment * 1) + (cohesion * 1)) * 0.05;
	}
	catch (int e)
	{
		// if nearby boid array is empty
		//FString errorNumberString = FString::FromInt(e);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, errorNumberString);
		e += 1;
		return GetVelocity();
	}
}

FVector ABoid::SeparateBoid(std::vector<FVector> nearbyBoidLocations)
{
	FVector actorLocation = GetActorLocation();

	try 
	{
		if (nearbyBoidLocations.size() == 0)
		{
			throw 10000;
		}

		FVector separationSteer = actorLocation - nearbyBoidLocations[0];

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
	catch (int e)
	{
		throw e;
	}
}

FVector ABoid::AlignBoid(std::vector<FRotator> nearbyBoidRotations)
{
	try
	{
		if (nearbyBoidRotations.size() == 0)
		{
			throw 10000;
		}

		FRotator actorRotation = GetActorRotation();

		FRotator alignmentSteer = nearbyBoidRotations[0] - actorRotation;

		for (int i = 0; i < nearbyBoidRotations.size(); i++) {
			FRotator nbRotation = nearbyBoidRotations[i];

			FRotator diff = nbRotation - actorRotation;
			alignmentSteer += diff;
		}

		//average out the alignment
		return alignmentSteer.Vector() / nearbyBoidRotations.size();
	}
	catch (int e)
	{		
		throw e;
	}
}

FVector ABoid::CohereBoid(std::vector<FVector> nearbyBoidLocations)
{
	try
	{
		if (nearbyBoidLocations.size() == 0)
		{
			throw 10000;
		}

		FVector cohesionSteer = FVector(0, 0, 0);
		FVector actorLocation = GetActorLocation();

		FVector totalLocations = nearbyBoidLocations[0]; //WHAT IF IT'S EMPTY - TODO

		for (int i = 1; i < nearbyBoidLocations.size(); i++) {
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
	catch (int e)
	{
		throw e;
	}
}

