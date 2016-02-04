// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AInputController : public APlayerController
{
	GENERATED_BODY()

		AInputController(const FObjectInitializer& ObjectInitializer);

		virtual void BeginPlay() override;

		// Called every frame
		virtual void Tick(float DeltaSeconds) override;

		virtual void SetupInputComponent();

		void OnLeftClick();
	
	
};
