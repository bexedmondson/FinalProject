// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Agent.generated.h"

#define FloorChannel ECC_Pawn

UCLASS()
class FINALPROJECT_API AAgent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetGlobalBest(FVector gBest);
	FVector GetAgentBest();

	FVector agentBestPosition;
	FVector globalBestPosition;

	FVector currentVelocity;

protected:
	UStaticMeshComponent* AgentMesh;

	void CheckAgentBest();
	FVector AlignToLandscape(FVector location);

	FVector CalculateAgentVelocity();
	
	bool Trace(
		UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = FloorChannel,
		bool ReturnPhysMat = false
		);
};
