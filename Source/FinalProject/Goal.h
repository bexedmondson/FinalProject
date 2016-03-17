// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{ 
	PLAYER		UMETA(DisplayName = "Player"),
	NEUTRAL		UMETA(DisplayName = "Neutral"),
	ENEMY		UMETA(DisplayName = "Enemy")
};

UCLASS()
class FINALPROJECT_API AGoal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Enum)
	ETeam team;
	
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
	ETeam GetTeam();
};