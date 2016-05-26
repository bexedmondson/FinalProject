// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalProject.h"
#include "Arrow.h"

static const float ACTOR_SCALE = 12.0f;
UAnimSequence* bounce;

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// static mesh for visualisation
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CubeMeshAsset(TEXT("SkeletalMesh'/Game/Meshes/arrow2_0.arrow2_0'"));
	if (CubeMeshAsset.Succeeded())
	{
		PrimaryActorTick.bCanEverTick = true;
		ArrowMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArrowMesh"));
		ArrowMesh->SetSkeletalMesh(CubeMeshAsset.Object);
		RootComponent = ArrowMesh;
		SetActorEnableCollision(false);
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT("AnimSequence'/Game/Meshes/arrow2_0_Anim_Cylinder_CylinderAction.arrow2_0_Anim_Cylinder_CylinderAction'"));
	bounce = anim.Object;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
	// scale to be more easily visible
	SetActorScale3D(FVector(ACTOR_SCALE, ACTOR_SCALE, ACTOR_SCALE));

	ArrowMesh->PlayAnimation(bounce, true);
}

// Called every frame
void AArrow::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

