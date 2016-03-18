// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Agent.h"

static const float ACTOR_SCALE = 30.0f;


// Sets default values
AAgent::AAgent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// static mesh for visualisation
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Meshes/agent0_0.agent0_0'"));
	if (CubeMeshAsset.Succeeded())
	{
		PrimaryActorTick.bCanEverTick = true;
		AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));
		AgentMesh->SetStaticMesh(CubeMeshAsset.Object);
		RootComponent = AgentMesh;
		SetActorEnableCollision(true);
	}
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();

	// scale to be more easily visible
	SetActorScale3D(FVector(ACTOR_SCALE, ACTOR_SCALE, ACTOR_SCALE));

	agentBestPosition = GetActorLocation();
}

// Called every frame
void AAgent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	CheckAgentBest();

	newVelocity = GetAgentVelocity();
}

void AAgent::CheckAgentBest()
{
	FVector currentLocation = GetActorLocation();

	if (currentLocation.Z > agentBestPosition.Z)
	{
		agentBestPosition = currentLocation;
	}
}

FVector AAgent::GetAgentVelocity()
{
	return FVector::ZeroVector;
}

void AAgent::SetGlobalBest(FVector gBest)
{
	globalBestPosition = gBest;
}

FVector AAgent::GetAgentBest()
{
	return agentBestPosition;
}

//this utility code taken from https://wiki.unrealengine.com/Trace_Functions
bool AAgent::Trace(
	UWorld* World,
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel,
	bool ReturnPhysMat
	) 
{
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingle(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
		);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);
}

