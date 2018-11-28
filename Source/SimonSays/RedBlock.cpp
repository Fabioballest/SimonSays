// Fill out your copyright notice in the Description page of Project Settings.


#include "RedBlock.h"
#include "SimonSaysBlock.h"
#include "SimonSaysBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"

ARedBlock::ARedBlock() : AccumulatedDeltaTime(0.0f), TimeBetweenBlock(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	auto BlockMesh = Super::GetBlockMesh();
	auto AuxMaterial = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"));
	RedMaterial = AuxMaterial.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> Soundf(TEXT("/Game/Puzzle/Audio/c6lsoft.c6lsoft"));
	Sound = Soundf.Object;

	Id = 1;

	BlockMesh->SetMaterial(0, RedMaterial);
	BlockMesh->OnClicked.AddDynamic(this, &ARedBlock::BlockClicked);
}

void ARedBlock::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (bIsActive) {
		AccumulatedDeltaTime += DeltaSeconds;
		SwitchOff();
	}

}

void ARedBlock::BlockClicked(UPrimitiveComponent * ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void ARedBlock::HandleClicked()
{
	if (!OwningGrid->IsPlaying()) {
		auto BlockMesh = Super::GetBlockMesh();
		PlaySound();
		// Change material
		BlockMesh->SetMaterial(0, RedMaterial);
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

void ARedBlock::Highlight(bool bOn)
{
	
	if (!OwningGrid->IsPlaying()) {
			auto BlockMesh = Super::GetBlockMesh();

			if (bOn)
			{
				BlockMesh->SetMaterial(0, BaseMaterial);
				
			}
			else
			{
				BlockMesh->SetMaterial(0, RedMaterial);
				
			}
			//AccumulatedDeltaTime = 0;
		
	}
	else {
		return;
		
	}
}

void ARedBlock::PlaySound() {
	UGameplayStatics::PlaySound2D(GetWorld(), Sound, 1.0f, 1.0f, 0.0f, nullptr);

}

void ARedBlock::SetId(int id)
{
	Id = id;
}


int ARedBlock::GetId() {
	return Id;
}


void ARedBlock::SwitchOn(float timer) {
	TimeBetweenBlock = timer;
	auto BlockMesh = Super::GetBlockMesh();
	bIsActive = true;
	AccumulatedDeltaTime = 0.0;
	BlockMesh->SetMaterial(0, BaseMaterial);
	PrimaryActorTick.bCanEverTick = true;
}

void ARedBlock::SwitchOff() {
	if (AccumulatedDeltaTime > TimeBetweenBlock) {
		AccumulatedDeltaTime = 0.0f;
		auto BlockMesh = Super::GetBlockMesh();
		BlockMesh->SetMaterial(0, RedMaterial);
		PrimaryActorTick.bCanEverTick = false;
		bIsActive = false;
	}

}