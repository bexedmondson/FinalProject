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
	currentVelocity = FVector(FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(-0.5f, 0.5f));
	//currentVelocity = FVector(0, 0, 0);

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
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "NOT EMPTY");

		return CohereBoid(nearbyBoidLocations) + AlignBoid(nearbyBoidRotations) + SeparateBoid(nearbyBoidLocations) * 0.001;
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
		if (nearbyBoidLocations.size() == 0) // fix!!
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
	FRotator actorRotation = GetActorRotation();
	
	try
	{
		if (nearbyBoidRotations.size() == 0) // fix!!
		{
			throw 10000;
		}

		float yaw = actorRotation.Yaw;

		FString errorNumberString = FString::FromInt(yaw);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, errorNumberString);

		FRotator alignmentSteer = nearbyBoidRotations[0] - actorRotation;
		float totalPitch = nearbyBoidRotations[0].Pitch;
		float totalYaw = nearbyBoidRotations[0].Yaw;
		float totalRoll = nearbyBoidRotations[0].Roll;

		for (int i = 0; i < nearbyBoidRotations.size(); i++) {
			FRotator nbRotation = nearbyBoidRotations[i];

			totalPitch += nbRotation.Pitch;
			totalYaw += nbRotation.Yaw;
			totalRoll += nbRotation.Roll;
		}

		//average out the alignment
		totalPitch = totalPitch / nearbyBoidRotations.size();
		totalYaw = totalYaw / nearbyBoidRotations.size();
		totalRoll = totalRoll / nearbyBoidRotations.size();

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

FVector ABoid::CohereBoid(std::vector<FVector> nearbyBoidLocations)
{
	FVector actorLocation = GetActorLocation();
	
	try
	{
		if (nearbyBoidLocations.size() == 0)
		{
			throw 10000; // fix!!
		}

		FVector cohesionSteer = nearbyBoidLocations[0] - actorLocation; // fix

		for (int i = 1; i < nearbyBoidLocations.size(); i++) {
			FVector nbLocation = nearbyBoidLocations[i];

			if (actorLocation != nbLocation)
			{
				//other location - current location because steering towards other location
				FVector diff = nbLocation - actorLocation;

				cohesionSteer += diff;
			}
		}

		//average out the total and get the direction this boid should be steering in
		return cohesionSteer / nearbyBoidLocations.size();
	}
	catch (int e)
	{
		throw e;
	}
}

