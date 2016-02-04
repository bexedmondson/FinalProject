// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "InputController.h"


AInputController::AInputController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using custom InputController!"));
	}

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


}

//FHitResult TraceResult(ForceInit);
//PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);
//FString TraceString;
//if (TraceResult.GetActor() != nullptr)
//{
	//TraceString += FString::Printf(TEXT("Trace Actor %s."), *TraceResult.GetActor()->GetName());
//}
//if (TraceResult.GetComponent() != nullptr)
//{
//	TraceString += FString::Printf(TEXT("Trace Comp %s."), *TraceResult.GetComponent()->GetName());
//}
