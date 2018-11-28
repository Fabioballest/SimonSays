// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueBlock.h"
#include "SimonSaysBlock.h"
#include "SimonSaysBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"

ABlueBlock::ABlueBlock() : AccumulatedDeltaTime(0.0f), TimeBetweenBlock (0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	auto BlockMesh = Super::GetBlockMesh();
	auto AuxMaterial = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"));
	
	static ConstructorHelpers::FObjectFinder<USoundBase> Soundf(TEXT("/Game/Puzzle/Audio/a2lsoft.a2lsoft"));
	Sound = Soundf.Object;

	Id = 0;

	BlueMaterial = AuxMaterial.Object;
	BlockMesh->SetMaterial(0, BlueMaterial);
	BlockMesh->OnClicked.AddDynamic(this, &ABlueBlock::BlockClicked);
}

void ABlueBlock::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (bIsActive) {
		AccumulatedDeltaTime += DeltaSeconds;
		SwitchOff();
	}

}

void ABlueBlock::BlockClicked(UPrimitiveComponent * ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void ABlueBlock::HandleClicked()
{
	if (!OwningGrid->IsPlaying()) {
		auto BlockMesh = Super::GetBlockMesh();
		bIsActive = true;
		PlaySound();
		// Change material
		BlockMesh->SetMaterial(0, BlueMaterial);
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

void ABlueBlock::Highlight(bool bOn)
{

	if (!OwningGrid->IsPlaying()) {
		
			auto BlockMesh = Super::GetBlockMesh();
			if (bOn)
			{
				BlockMesh->SetMaterial(0, BaseMaterial);
			}
			else
			{
				BlockMesh->SetMaterial(0, BlueMaterial);
			}
			
		
	}
	else {
		return;
	}
}

void ABlueBlock::SwitchOn(float timer) {
	TimeBetweenBlock = timer;
	auto BlockMesh = Super::GetBlockMesh();
	bIsActive = true;
	AccumulatedDeltaTime = 0.0;
	BlockMesh->SetMaterial(0, BaseMaterial);
	PrimaryActorTick.bCanEverTick = true;
}

void ABlueBlock::SwitchOff() {
	if (AccumulatedDeltaTime > TimeBetweenBlock) {
		AccumulatedDeltaTime = 0.0f;
		auto BlockMesh = Super::GetBlockMesh();
		BlockMesh->SetMaterial(0, BlueMaterial);
		PrimaryActorTick.bCanEverTick = false;
		bIsActive = false;
	}

}
void ABlueBlock::PlaySound() {
	UGameplayStatics::PlaySound2D(GetWorld(), Sound, 1.0f, 1.0f, 0.0f, nullptr);
}

void ABlueBlock::SetId(int id)
{
	Id = id;
}

int ABlueBlock::GetId() {
	return Id;
}