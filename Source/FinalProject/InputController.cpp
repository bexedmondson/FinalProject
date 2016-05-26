// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "InputController.h"
#include "BoidController.h"
#include "Arrow.h"

ABoidController* boidControllerPtr;
AArrow* indicator;

AInputController::AInputController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;

	// Initialize audio component
	static ConstructorHelpers::FObjectFinder<USoundCue> windSound(TEXT("SoundCue'/Game/Sounds/WindCue.WindCue'"));
	windAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("WindAudioComponent"));
	windAudioComponent->SetSound(windSound.Object);
	windAudioComponent->AttachParent = RootComponent;
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

	if (indicator != NULL) {
		indicator->Destroy();
	}
	indicator = GetWorld()->SpawnActor<AArrow>(AArrow::StaticClass(), clickedPosition, FRotator::ZeroRotator);

	boidControllerPtr->SetControllerTarget(clickedPosition);

	windAudioComponent->SetWorldLocation(clickedPosition);
	windAudioComponent->Play();
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
