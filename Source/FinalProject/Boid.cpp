// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Boid.h"

// constants for this file
static const float OUTER_SPHERE_RADIUS = 10.0f; // for cohesion and alignment
static const float INNER_SPHERE_RADIUS = 50.0f; // for separation - I don't know why this one has to be a bigger number for a smaller sphere, units make no sense

static const float ACTOR_SCALE = 12.0f;

// coefficients for boids algorithm
static const float SEPARATION_COEFFICIENT = 0.09;
static const float ALIGNMENT_COEFFICIENT = 0.04;
static const float COHESION_COEFFICIENT = 0.04;
static const float BOUNDING_BOX_COEFFICIENT = 0.005;

static const float MAX_SPEED = 4;

static const float BOUNDING_BOX_SIZE = 200;
static const float AVERAGE_DIST_ABOVE_FLOOR = 100;
static const float MIN_DIST_ABOVE_FLOOR = 50;


// sets default values
ABoid::ABoid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set this actor to call Tick() every frame.
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
	SphereComponent->InitSphereRadius(OUTER_SPHERE_RADIUS);
	SphereComponent->SetCollisionProfileName("BoidCollider");
}

// called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();

	// scale to be more easily visible
	SetActorScale3D(FVector(ACTOR_SCALE, ACTOR_SCALE, ACTOR_SCALE));

	//initialise velocity
	currentVelocity = FVector(FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(-0.5f, 0.5f));

	//initialise rotation
	rotation = FRotator::ZeroRotator;

	//initialise bounding box
	boundingBoxCorner = FVector(-100, 100, -100);
}

// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// calculate new velocity and rotation
	FVector totalVelocity = (currentVelocity + CalculateBoidVelocity()).GetClampedToMaxSize(MAX_SPEED);
	rotation = totalVelocity.Rotation();

	SetActorLocationAndRotation(GetActorLocation() + totalVelocity, rotation);

	currentVelocity = totalVelocity;
}

FVector ABoid::CalculateBoidVelocity()
{
	// get nearby objects
	TArray<UPrimitiveComponent*> nearbyComponents;
	GetOverlappingComponents(nearbyComponents);
	
	// initialise arrays to hold information
	TArray<FVector> immediateBoidLocations;
	TArray<FVector> nearbyBoidLocations;
	TArray<FRotator> nearbyBoidRotations;

	// iterate over components to find only the boids
	for (int i = 0; i < nearbyComponents.Num(); i++)
	{
		UPrimitiveComponent* collidingComponent = nearbyComponents[i];
		AActor* colliderOwner = collidingComponent->GetOwner();

		// if it's a boid, add its info to the arrays
		if (colliderOwner->IsA(ABoid::StaticClass()))
		{
			nearbyBoidRotations.AddUnique(colliderOwner->GetActorRotation());
			nearbyBoidLocations.AddUnique(colliderOwner->GetActorLocation());

			// if distance is below threshold, add to closer boid array
			if (GetDistanceTo(colliderOwner) < INNER_SPHERE_RADIUS)
			{
				immediateBoidLocations.AddUnique(colliderOwner->GetActorLocation());
			}
		}
	}

	FVector total;

	if (nearbyBoidLocations.Num() == 0)
	{
		// there are no nearby boids, just stay in box
		FVector b = KeepBoidInBox() * BOUNDING_BOX_COEFFICIENT;

		total = b;
	}
	else if (immediateBoidLocations.Num() == 0)
	{
		// no boids to steer away from
		FVector a = AlignBoid(nearbyBoidRotations) * ALIGNMENT_COEFFICIENT;
		FVector c = CohereBoid(nearbyBoidLocations) * COHESION_COEFFICIENT;
		FVector b = KeepBoidInBox() * BOUNDING_BOX_COEFFICIENT;

		total = a + c + b;
	}
	else
	{
		// everything is there, proceed normally
		FVector s = SeparateBoid(immediateBoidLocations) * SEPARATION_COEFFICIENT;
		FVector a = AlignBoid(nearbyBoidRotations) * ALIGNMENT_COEFFICIENT;
		FVector c = CohereBoid(nearbyBoidLocations) * COHESION_COEFFICIENT;
		FVector b = KeepBoidInBox() * BOUNDING_BOX_COEFFICIENT;

		total = s + a + c + b;
	}

	return total;
}

FVector ABoid::SeparateBoid(TArray<FVector> immediateBoidLocations)
{
	FVector actorLocation = GetActorLocation();

	FVector separationSteer = actorLocation - immediateBoidLocations[0];

	// calculate difference in location for each nearby boid
	for (int i = 0; i < immediateBoidLocations.Num(); i++) {
		FVector nbLocation = immediateBoidLocations[i];

		if (actorLocation != nbLocation)
		{
			// current location - other location because steering away from other location
			FVector diff = actorLocation - nbLocation;

			separationSteer += diff;
		}
	}

	// average out the steer
	return separationSteer / immediateBoidLocations.Num();
}

FVector ABoid::AlignBoid(TArray<FRotator> nearbyBoidRotations)
{
	FRotator actorRotation = GetActorRotation();
	
	FRotator alignmentSteer = nearbyBoidRotations[0] - actorRotation;
	float totalPitch = nearbyBoidRotations[0].Pitch;
	float totalYaw = nearbyBoidRotations[0].Yaw;
	float totalRoll = nearbyBoidRotations[0].Roll;

	// calculate difference in roation for each nearby boid
	for (int i = 0; i < nearbyBoidRotations.Num(); i++) {
		FRotator nbRotation = nearbyBoidRotations[i];

		totalPitch += nbRotation.Pitch;
		totalYaw += nbRotation.Yaw;
		totalRoll += nbRotation.Roll;
	}

	// average out the alignment
	totalPitch = totalPitch / nearbyBoidRotations.Num();
	totalYaw = totalYaw / nearbyBoidRotations.Num();
	totalRoll = totalRoll / nearbyBoidRotations.Num();

	alignmentSteer = FRotator(totalPitch - actorRotation.Pitch, 
								totalYaw - actorRotation.Yaw, 
								totalRoll - actorRotation.Roll);

	return alignmentSteer.Vector();
}

FVector ABoid::CohereBoid(TArray<FVector> nearbyBoidLocations)
{
	FVector actorLocation = GetActorLocation();

	FVector cohesionSteer = nearbyBoidLocations[0] - actorLocation;

	// calculate difference in location for each very near boid
	for (int i = 1; i < nearbyBoidLocations.Num(); i++) {
		FVector nbLocation = nearbyBoidLocations[i];

		if (actorLocation != nbLocation)
		{
			// other location - current location because steering towards other location
			FVector diff = nbLocation - actorLocation;

			cohesionSteer += diff;
		}
	}

	// average out the total and get the direction this boid should be steering in
	return cohesionSteer / nearbyBoidLocations.Num();
}

FVector ABoid::KeepBoidInBox()
{
	FVector actorLocation = GetActorLocation();

	FVector boxSteer = FVector::ZeroVector;

	FBox boundingBox = FBox(boundingBoxCorner, boundingBoxCorner + BOUNDING_BOX_SIZE);

	// calculate vector towards centre of target box if the boid is not already in the box
	if (!boundingBox.IsInside(actorLocation))
	{
		boxSteer = boundingBox.GetCenter() - actorLocation;
	}

	return boxSteer;
}

void ABoid::SetTarget(FVector boidTarget)
{
	boundingBoxCorner = boidTarget - FVector(BOUNDING_BOX_SIZE, BOUNDING_BOX_SIZE, BOUNDING_BOX_SIZE);
	boundingBoxCorner.Z += AVERAGE_DIST_ABOVE_FLOOR;
}

// test function
FVector ABoid::GetCurrentVelocity()
{
	return currentVelocity;
}

// test function
void ABoid::SetCurrentVelocity(FVector velocity)
{
	currentVelocity = velocity;
}