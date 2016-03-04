// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Goal.h"


// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// static mesh for visualisation
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Meshes/goal0_1.goal0_1'"));
	if (CubeMeshAsset.Succeeded())
	{
		PrimaryActorTick.bCanEverTick = true;
		GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalMesh"));
		GoalMesh->SetStaticMesh(CubeMeshAsset.Object);
		RootComponent = GoalMesh;
		SetActorEnableCollision(true);
	}

	// attach sphere for detecting nearby boids
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->AttachTo(RootComponent);
	SphereComponent->InitSphereRadius(40.0);
	SphereComponent->SetCollisionProfileName("GoalCollider");
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

