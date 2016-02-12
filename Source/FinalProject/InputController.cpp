// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "InputController.h"
#include "BoidController.h"

ABoidController* boidControllerPtr;

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
	//startTrace = startTrace + traceDirection * ((boidControllerPtr->GetActorLocation() - startTrace) | traceDirection);
	//i don't know if i need that^ so i'm leaving it commented

	//calculate end point of trace
	const float clickRange = 4096.0f;
	const FVector endTrace = startTrace + traceDirection * clickRange;

	//setup trace query
	static FName clickTraceIdent = FName(TEXT("clickTrace"));
	FCollisionQueryParams traceParams(clickTraceIdent, true, this);
	traceParams.bTraceAsyncScene = true;

	//perform the trace
	GetWorld()->LineTraceSingleByChannel(landscapePosition, startTrace, endTrace, ECC_GameTraceChannel1, traceParams);

	FVector clickPoint = landscapePosition.Location;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, clickPoint.ToString());
	}

	return clickPoint;
}

void AInputController::SetBoidControllerPtr(ABoidController* bControllerPtr)
{
	boidControllerPtr = bControllerPtr;
}
