// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonSaysBlock.h"
#include "SimonSaysBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Materials/MaterialInstance.h"

ASimonSaysBlock::ASimonSaysBlock() : AccumulatedDeltaTime(0)
{
	PrimaryActorTick.bCanEverTick = true;
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;

		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetupAttachment(DummyRoot);
	//BlockMesh->OnClicked.AddDynamic(this, &ASimonSaysBlock::BlockClicked);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
}

void ASimonSaysBlock::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	AccumulatedDeltaTime += DeltaSeconds;



}


void ASimonSaysBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ASimonSaysBlock::HandleClicked()
{
	// Check we are not already active
	
		bIsActive = true;
		if (bIsActive) {
			// Change material
			BlockMesh->SetMaterial(0, YellowMaterial);
			// Tell the Grid
			if (OwningGrid != nullptr)
			{
				OwningGrid->AddScore();
			}
		}
}

void ASimonSaysBlock::Highlight(bool bOn)
{

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlockMesh->GetMaterial(1));
	}
}

void ASimonSaysBlock::SetId(int id)
{
	Id = id;
}


int ASimonSaysBlock::GetId() {
	return Id;
}

void ASimonSaysBlock::PlaySound() {

}


void ASimonSaysBlock::SwitchOn(float timer) {
	AccumulatedDeltaTime = 0.0f;
	if (!OwningGrid->IsPlaying()) {
		//if (AccumulatedDeltaTime > 2.0) {
		

		//}
	}
	else {
		return;
	}

}

void ASimonSaysBlock::SwitchOff() {
	AccumulatedDeltaTime = 0.0f;
	if (!OwningGrid->IsPlaying()) {
		if (AccumulatedDeltaTime > 2.0) {
			
		}
	}
	else {
		return;
	}

}