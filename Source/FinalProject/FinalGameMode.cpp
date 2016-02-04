// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "FinalGameMode.h"
#include "BoidController.h"
#include "Boid.h"
#include "InputController.h"

AFinalGameMode::AFinalGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AInputController::StaticClass();
}

void AFinalGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	ABoidController* boidController = GetWorld()->SpawnActor<ABoidController>(ABoidController::StaticClass());

}


