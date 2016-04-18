// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Goal.h"
#include "GoalController.generated.h"

UCLASS()
class FINALPROJECT_API AGoalController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Player Goal Score */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GoalScore)
	int32 PlayerGoalScore;

	/** Neutral Goal Score */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GoalScore)
	int32 NeutralGoalScore;

	/** Enemy Goal Score */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GoalScore)
	int32 EnemyGoalScore;

protected:
	
	void CalculateScores();

	// test function
	TArray<AGoal*> GetGoalArray();
};
