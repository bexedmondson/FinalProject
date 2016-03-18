// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "AgentController.h"


// Sets default values
AAgentController::AAgentController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgentController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAgentController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

