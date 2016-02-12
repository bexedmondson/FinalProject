// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "InputController.h"
#include "FinalGameMode.generated.h"

/**
*
*/
UCLASS()
class FINALPROJECT_API AFinalGameMode : public AGameMode
{
	GENERATED_BODY()

	AFinalGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;

	//override spawnplayercontroller sp we can get a reference to the controller
	virtual APlayerController* SpawnPlayerController(ENetRole RemotrRole, FVector const& SpawnLocation, FRotator const& SpawnRotation) override;

	UPROPERTY()
	AInputController* inputControllerPtr;
};
