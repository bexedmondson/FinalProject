// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoidController.h"
#include "TestBoidController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ATestBoidController : public ABoidController
{
	GENERATED_BODY()
	
public:
	ATestBoidController(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FString TestGenerateCorrectNumberOfBoids();
	FString TestGenerateBoidsOnlyInBox();
};
