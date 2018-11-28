// Fill out your copyright notice in the Description page of Project Settings.


#include "YellowBlock.h"
#include "SimonSaysBlock.h"
#include "SimonSaysBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"

AYellowBlock::AYellowBlock() : AccumulatedDeltaTime(0.0f), TimeBetweenBlock(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	auto BlockMesh = Super::GetBlockMesh();
	auto AuxMaterial = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("/Game/Puzzle/Meshes/YellowMaterial.YellowMaterial"));
	YellowMaterial = AuxMaterial.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> Soundf(TEXT("/Game/Puzzle/Audio/c4lsoft.c4lsoft"));
	Sound = Soundf.Object;

	Id = 3;

	BlockMesh->SetMaterial(0, YellowMaterial);
	BlockMesh->OnClicked.AddDynamic(this, &AYellowBlock::BlockClicked);
}

void AYellowBlock::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (bIsActive) {
		AccumulatedDeltaTime += DeltaSeconds;
		SwitchOff();
	}

}

void AYellowBlock::BlockClicked(UPrimitiveComponent * ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void AYellowBlock::HandleClicked()
{
	auto BlockMesh = Super::GetBlockMesh();
	bIsActive = true;
	if (!OwningGrid->IsPlaying()) {
		// Change material
		PlaySound();
		BlockMesh->SetMaterial(0, YellowMaterial);
		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->CheckSequence(Id);
		}
	}
	else {
		return;
	}
}

void AYellowBlock::Highlight(bool bOn)
{
	if (!OwningGrid->IsPlaying()) {

		
			auto BlockMesh = Super::GetBlockMesh();
			if (bOn)
			{
				BlockMesh->SetMaterial(0, BaseMaterial);
				
			}
			else
			{
				BlockMesh->SetMaterial(0, YellowMaterial);
				
			}
			
		
	}
	else {
		return;
	}
	
}


void AYellowBlock::PlaySound() {
	UGameplayStatics::PlaySound2D(GetWorld(), Sound, 1.0f, 1.0f, 0.0f, nullptr);

}

void AYellowBlock::SetId(int id)
{
	Id = id;
}

int AYellowBlock::GetId()
{
	return Id;
}


void AYellowBlock::SwitchOn(float timer) {
	TimeBetweenBlock = timer;
	auto BlockMesh = Super::GetBlockMesh();
	bIsActive = true;
	AccumulatedDeltaTime = 0.0;
	BlockMesh->SetMaterial(0, BaseMaterial);
	PrimaryActorTick.bCanEverTick = true;
}

void AYellowBlock::SwitchOff() {
	if (AccumulatedDeltaTime > TimeBetweenBlock) {
		AccumulatedDeltaTime = 0.0f;
		auto BlockMesh = Super::GetBlockMesh();
		BlockMesh->SetMaterial(0, YellowMaterial);
		PrimaryActorTick.bCanEverTick = false;
		bIsActive = false;
	}

}