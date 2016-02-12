// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "InputController.h"


AInputController::AInputController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bEnableClickEvents = true;
}

void AInputController::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AInputController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInputController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	this->InputComponent->BindAction("LeftClick", EInputEvent::IE_Pressed, this, &AInputController::OnLeftClick);
}

void AInputController::OnLeftClick()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("click!"));
	}

	FVector clickedPosition = GetClickedPosition();
}

FVector AInputController::GetClickedPosition()
{
	//code adapted from linetracesingle example in unreal engine documentation

	//this is what we get the location from
	FHitResult landscapePosition;

	//calculate the direction the camera is looking
	FVector cameraLocation;
	FRotator cameraRotation;
	GetPlayerViewPoint(cameraLocation, cameraRotation);
	const FVector traceDirection = cameraRotation.Vector();

	//calculate the start position for the trace
	FVector startTrace = FVector::ZeroVector;
	FRotator unusedRotation;
	GetPlayerViewPoint(startTrace, unusedRotation);

	//adjust trace so there's nothing blocking the ray between the camera and the pawn and calculate distance from adjusted start
	//startTrace = startTrace + traceDirection * ((GetActorLocation() - startTrace) | traceDirection);

	return FVector();
}
