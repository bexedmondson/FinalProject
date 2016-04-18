// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{ 
	PLAYER,		
	NEUTRAL,	
	ENEMY		
};

UCLASS()
class FINALPROJECT_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	ETeam GetTeam();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Enum)
	ETeam team;

	// test functions
	void SetTeam(ETeam team);

protected:
	UStaticMeshComponent* GoalMesh;

	void CheckForActorsInSphere();
};