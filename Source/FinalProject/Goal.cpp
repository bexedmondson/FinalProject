// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Goal.h"
#include "Boid.h"

static const float ACTOR_SCALE = 20.0f;
static const FColor PLAYER_COLOUR = FColor::Green;
static const FColor NEUTRAL_COLOUR = FColor::Yellow;
static const FColor ENEMY_COLOUR = FColor::Red;

Team team = Team::Neutral;

UMaterialInstance* goalMaterial;

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

		static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialInstance(TEXT("MaterialInstanceConstant'/Game/Materials/GoalMaterialInst.GoalMaterialInst'"));
		if (MaterialInstance.Object != NULL)
		{
			goalMaterial = (UMaterialInstance*)MaterialInstance.Object;
			GoalMesh->SetMaterial(0, goalMaterial);
		}
	}

	// scale to be more easily visible
	SetActorScale3D(FVector(ACTOR_SCALE, ACTOR_SCALE, ACTOR_SCALE));

	// attach sphere for detecting nearby boids
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->AttachTo(RootComponent);
	SphereComponent->InitSphereRadius(20.0);
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

	CheckForActorsInSphere();
}

void AGoal::CheckForActorsInSphere()
{
	// get nearby objects
	TArray<UPrimitiveComponent*> nearbyComponents;
	GetOverlappingComponents(nearbyComponents);

	// initialise count to hold number of boids
	int numOfBoidsInSphere = 0;

	//initialise list of AI actors so they can be set to redistribute
	//TO BE DONE IN LATER ISSUE
	
	TArray<FVector> nearbyBoidLocations;

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
		else if (false)
		{
			//this is where the check for AI will go
		}
	}

	if (numOfBoidsInSphere > 10) //&& enemyNum < 3
	{
		team = Team::Player;
		SetTeamColour();
	}
	//else if numOfBoids < 10 && enemyNum > 3
	//team = Team::Enemy
	//SetTeamColour();
	//else if numOfBoids > 10 && enemyNum > 3 
	//both teams are fighting over the same one, set to neutral
	//team = Team::Neutral
	//SetTeamColour();
}

void AGoal::SetTeamColour()
{
	FString teamString;

	if (team == Team::Player)
	{
		goalMaterial->SetVectorParameterValue("GoalColor", PLAYER_COLOUR);
		teamString = "player";
	}
	else if (team == Team::Neutral)
	{
		goalMaterial->SetVectorParameterValue("GoalColor", NEUTRAL_COLOUR);
		teamString = "neutral";
	}
	else if (team == Team::Enemy)
	{
		goalMaterial->SetVectorParameterValue("GoalColor", ENEMY_COLOUR);
		teamString = "enemy";
	}


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, teamString);
	}
}

Team AGoal::GetTeam()
{
	return team;
}
