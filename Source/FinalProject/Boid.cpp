// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Boid.h"

// constants for this file
static const float OUTER_SPHERE_RADIUS = 10.0f;
static const float INNER_SPHERE_RADIUS = 50.0f;

static const float ACTOR_SCALE = 12.0f;

static const float SEPARATION_COEFFICIENT = 0.01;
static const float ALIGNMENT_COEFFICIENT = 0.02;
static const float COHESION_COEFFICIENT = 0.04;

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
	rotation = FRotator(0.0, 0.0, 0.0);

}

// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	newVelocity = CalculateBoidVelocity();

	FVector totalVelocity = currentVelocity + newVelocity;

	rotation = totalVelocity.Rotation();

	SetActorLocationAndRotation(GetActorLocation() + totalVelocity, rotation);

	currentVelocity = totalVelocity;
}

void ABoid::SetVelocity(FVector velocity) 
{
	newVelocity = velocity;
}

FVector ABoid::CalculateBoidVelocity()
{
	TArray<UPrimitiveComponent*> nearbyComponents;
	GetOverlappingComponents(nearbyComponents);
	
	TArray<FVector> immediateBoidLocations;
	TArray<FVector> nearbyBoidLocations;
	TArray<FRotator> nearbyBoidRotations;

	// iterate over components to find only the boids
	for (int i = 0; i < nearbyComponents.Num(); i++)
	{
		UPrimitiveComponent* collidingComponent = nearbyComponents[i];
		AActor* colliderOwner = collidingComponent->GetOwner();

		if (colliderOwner->IsA(ABoid::StaticClass()))
		{
			// if boid array doesn't already have the boid in it
			nearbyBoidRotations.AddUnique(colliderOwner->GetActorRotation());
			nearbyBoidLocations.AddUnique(colliderOwner->GetActorLocation());

			// if distance is below threshold, add to closer boid array
			if (GetDistanceTo(colliderOwner) < INNER_SPHERE_RADIUS)
			{
				immediateBoidLocations.AddUnique(colliderOwner->GetActorLocation());
			}
		}
	}

	try
	{
		FVector s = SeparateBoid(immediateBoidLocations) * SEPARATION_COEFFICIENT;
		FVector a = AlignBoid(nearbyBoidRotations) * ALIGNMENT_COEFFICIENT;
		FVector c = CohereBoid(nearbyBoidLocations) * COHESION_COEFFICIENT;

		return s + a + c;
	}
	catch (int e)
	{
		e += 1;
		return currentVelocity;
	}
}

FVector ABoid::SeparateBoid(TArray<FVector> immediateBoidLocations)
{
	FVector actorLocation = GetActorLocation();

	try 
	{
		if (immediateBoidLocations.Num() == 0) // fix!!
		{
			throw 10000;
		}

		FVector separationSteer = actorLocation - immediateBoidLocations[0];

		for (int i = 0; i < immediateBoidLocations.Num(); i++) {
			FVector nbLocation = immediateBoidLocations[i];

			if (actorLocation != nbLocation)
			{
				//current location - other location because steering away from other location
				FVector diff = actorLocation - nbLocation;

				separationSteer += diff;
			}
		}

		//average out the steer
		return separationSteer / immediateBoidLocations.Num();
	}
	catch (int e)
	{
		throw e;
	}
}

FVector ABoid::AlignBoid(TArray<FRotator> nearbyBoidRotations)
{
	FRotator actorRotation = GetActorRotation();
	
	try
	{
		if (nearbyBoidRotations.Num() == 0) // fix!!
		{
			throw 10000;
		}

		FRotator alignmentSteer = nearbyBoidRotations[0] - actorRotation;
		float totalPitch = nearbyBoidRotations[0].Pitch;
		float totalYaw = nearbyBoidRotations[0].Yaw;
		float totalRoll = nearbyBoidRotations[0].Roll;

		for (int i = 0; i < nearbyBoidRotations.Num(); i++) {
			FRotator nbRotation = nearbyBoidRotations[i];

			totalPitch += nbRotation.Pitch;
			totalYaw += nbRotation.Yaw;
			totalRoll += nbRotation.Roll;
		}

		//average out the alignment
		totalPitch = totalPitch / nearbyBoidRotations.Num();
		totalYaw = totalYaw / nearbyBoidRotations.Num();
		totalRoll = totalRoll / nearbyBoidRotations.Num();

		alignmentSteer = FRotator(totalPitch - actorRotation.Pitch, 
								  totalYaw - actorRotation.Yaw, 
								  totalRoll - actorRotation.Roll);

		return alignmentSteer.Vector();
	}
	catch (int e)
	{		
		throw e;
	}
}

FVector ABoid::CohereBoid(TArray<FVector> nearbyBoidLocations)
{
	FVector actorLocation = GetActorLocation();
	
	try
	{
		if (nearbyBoidLocations.Num() == 0)
		{
			throw 10000; // fix!!
		}

		FVector cohesionSteer = nearbyBoidLocations[0] - actorLocation; // fix

		for (int i = 1; i < nearbyBoidLocations.Num(); i++) {
			FVector nbLocation = nearbyBoidLocations[i];

			if (actorLocation != nbLocation)
			{
				//other location - current location because steering towards other location
				FVector diff = nbLocation - actorLocation;

				cohesionSteer += diff;
			}
		}
		float size = cohesionSteer.Size();

		FString errorNumberString = FString::FromInt(size);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, errorNumberString);

		//average out the total and get the direction this boid should be steering in
		return cohesionSteer / nearbyBoidLocations.Num() * COHESION_COEFFICIENT;
	}
	catch (int e)
	{
		throw e;
	}
}

