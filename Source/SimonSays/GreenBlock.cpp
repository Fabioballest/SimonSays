// Fill out your copyright notice in the Description page of Project Settings.



#include "GreenBlock.h"
#include "SimonSaysBlock.h"
#include "SimonSaysBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"

AGreenBlock::AGreenBlock() :  AccumulatedDeltaTime(0.0f), TimeBetweenBlock(0.0f) {
	
	PrimaryActorTick.bCanEverTick = true;
	auto BlockMesh = Super::GetBlockMesh();
	auto AuxMaterial = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("/Game/Puzzle/Meshes/GreenMaterial.GreenMaterial"));
	GreenMaterial = AuxMaterial.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> Soundf(TEXT("/Game/Puzzle/Audio/a3lsoft.a3lsoft"));
	Sound = Soundf.Object;

	Id = 2;

	BlockMesh->SetMaterial(0, GreenMaterial);
	BlockMesh->OnClicked.AddDynamic(this, &AGreenBlock::BlockClicked);
}

void AGreenBlock::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (bIsActive) {
		AccumulatedDeltaTime += DeltaSeconds;
		SwitchOff();
	}

}

void AGreenBlock::BlockClicked(UPrimitiveComponent * ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void AGreenBlock::HandleClicked()
{
	auto BlockMesh = Super::GetBlockMesh();
	if (!OwningGrid->IsPlaying()) {
		bIsActive = true;
		PlaySound();

		// Change material
		BlockMesh->SetMaterial(0, GreenMaterial);
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

void AGreenBlock::Highlight(bool bOn)
{
	if (!OwningGrid->IsPlaying()) {
		
			auto BlockMesh = Super::GetBlockMesh();
			if (bOn)
			{
				BlockMesh->SetMaterial(0, BaseMaterial);
				
			}
			else
			{
				BlockMesh->SetMaterial(0, GreenMaterial);
				
			}
		
		
	}
	else {
		return;
	}
}

void AGreenBlock::PlaySound() {
	UGameplayStatics::PlaySound2D(GetWorld(), Sound, 1.0f, 1.0f, 0.0f, nullptr);

}

void AGreenBlock::SetId(int id)
{
	Id = id;
}
int AGreenBlock::GetId() {
	return Id;
}


void AGreenBlock::SwitchOn(float timer) {
	TimeBetweenBlock = timer;
	auto BlockMesh = Super::GetBlockMesh();
	bIsActive = true;
	AccumulatedDeltaTime = 0.0;
	BlockMesh->SetMaterial(0, BaseMaterial);
	PrimaryActorTick.bCanEverTick = true;
}

void AGreenBlock::SwitchOff() {
	if (AccumulatedDeltaTime > TimeBetweenBlock) {
		AccumulatedDeltaTime = 0.0f;
		auto BlockMesh = Super::GetBlockMesh();
		BlockMesh->SetMaterial(0, GreenMaterial);
		PrimaryActorTick.bCanEverTick = false;
		bIsActive = false;
	}

}