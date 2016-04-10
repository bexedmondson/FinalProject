// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Goal.generated.h"

enum class Team
{ 
	PLAYER,		
	NEUTRAL,	
	ENEMY		
};

UCLASS()
class FINALPROJECT_API AGoal : public AActor
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Enum)
	Team team;
	
public:	
	// Sets default values for this actor's properties
	AGoal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UStaticMeshComponent* GoalMesh;

	void CheckForActorsInSphere();

	FColor GetTeamColour();
	Team GetTeam();
};