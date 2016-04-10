// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Goal.h"
#include "Boid.h"
#include "Agent.h"

static const float ACTOR_SCALE = 20.0f;
static const FColor PLAYER_COLOUR = FColor::Green;
static const FColor NEUTRAL_COLOUR = FColor::Yellow;
static const FColor ENEMY_COLOUR = FColor::Red;

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

	// scale to be more easily visible
	SetActorScale3D(FVector(ACTOR_SCALE, ACTOR_SCALE, ACTOR_SCALE));

	// attach sphere for detecting nearby boids
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->AttachTo(RootComponent);
	SphereComponent->InitSphereRadius(20.0);
	SphereComponent->SetCollisionProfileName("GoalCollider");

	team = Team::NEUTRAL;
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

	CheckForActorsInSphere();

	if (team == Team::ENEMY) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "enemy");
	}
	else if (team == Team::NEUTRAL) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "neutral");
	}
	else if (team == Team::PLAYER)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "player");
	}
}

void AGoal::CheckForActorsInSphere()
{
	// get nearby objects
	TArray<UPrimitiveComponent*> nearbyComponents;
	GetOverlappingComponents(nearbyComponents);

	// initialise count to hold number of boids
	int numOfBoidsInSphere = 0;

	//initialise count to hold number of agents
	//also initialise list of AI actors so they can be set to redistribute
	int numOfAgentsInSphere = 0;
	TArray<AAgent*> nearbyAgents;

	// iterate over components to find only the boids
	for (int i = 0; i < nearbyComponents.Num(); i++)
	{
		UPrimitiveComponent* collidingComponent = nearbyComponents[i];
		AActor* colliderOwner = collidingComponent->GetOwner();

		// if it's a boid, increase the count
		if (colliderOwner->IsA(ABoid::StaticClass()))
		{
			numOfBoidsInSphere++;
		}
		else if (colliderOwner->IsA(AAgent::StaticClass()))
		{
			numOfAgentsInSphere++;
			nearbyAgents.AddUnique((AAgent*)colliderOwner); //have to cast here or doesn't build
		}
	}

	if (numOfBoidsInSphere > 10 && numOfAgentsInSphere < 5)
	{
		team = Team::PLAYER;
	}
	else if (numOfBoidsInSphere < 10 && numOfAgentsInSphere > 5)
	{
		team = Team::ENEMY;
		for (AAgent* agent : nearbyAgents)
		{
			agent->SetToBeRespawned();
		}
	}
	else if (numOfBoidsInSphere > 10 && numOfAgentsInSphere > 3)
	{
		//both teams are fighting over the same one, set to neutral
		team = Team::NEUTRAL;
	}
}

FColor AGoal::GetTeamColour()
{
	if (team == Team::PLAYER)
	{
		return PLAYER_COLOUR;
	}
	else if (team == Team::NEUTRAL)
	{
		return NEUTRAL_COLOUR;
	}
	else if (team == Team::ENEMY)
	{
		return ENEMY_COLOUR;
	}

	return FColor::White;
}

Team AGoal::GetTeam()
{
	return team;
}
