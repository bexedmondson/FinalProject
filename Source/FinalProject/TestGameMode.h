// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "InputController.h"
#include "CoreMisc.h"
#include "TestBoid.h"
#include "TestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ATestGameMode : public AGameMode
{
	GENERATED_BODY()

	ATestGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//override spawnplayercontroller so we can get a reference to the controller
	virtual APlayerController* SpawnPlayerController(ENetRole RemotrRole, FVector const& SpawnLocation, FRotator const& SpawnRotation) override;

	UPROPERTY()
	AInputController* inputControllerPtr;

protected:

	void RunTests();

	FString RunBoidControllerTests();
	FString RunBoidTests();
	FString RunAgentControllerTests();
	FString RunAgentTests();
	FString RunGoalControllerTests();
};
