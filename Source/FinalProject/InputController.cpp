// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "InputController.h"
#include "BoidController.h"

ABoidController* boidControllerPtr;

AInputController::AInputController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
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
	FVector clickedPosition = GetClickedPosition();

	boidControllerPtr->SetControllerTarget(clickedPosition);
}

FVector AInputController::GetClickedPosition()
{
	//initialise hit result
	FHitResult landscapePosition;

	//get click position
	GetHitResultUnderCursor(ECC_Visibility, false, landscapePosition);

	FVector clickPoint = landscapePosition.Location;

	return clickPoint;
}

void AInputController::SetBoidControllerPtr(ABoidController* bControllerPtr)
{
	boidControllerPtr = bControllerPtr;
}
