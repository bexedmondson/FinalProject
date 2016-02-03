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
}

void AInputController::BeginPlay()
{

}

void AInputController::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AInputController::OnLeftClick);
}

void AInputController::OnLeftClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("click!"));
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