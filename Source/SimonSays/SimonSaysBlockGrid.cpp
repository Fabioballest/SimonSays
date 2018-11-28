// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonSaysBlockGrid.h"
#include "SimonSaysBlock.h"
#include "RedBlock.h"
#include "BlueBlock.h"
#include "GreenBlock.h"
#include "YellowBlock.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine.h"
#include "SaveGameSimonSays.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ASimonSaysBlockGrid::ASimonSaysBlockGrid() : AccumulatedDeltaTime(0.0f), InitialTimer(0.0f), Score(0)
{
	PrimaryActorTick.bCanEverTick = true;
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = 2;
	BlockSpacing = 300.f;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> Soundf(TEXT("/Game/Puzzle/Audio/Sad_Trombone-Joe_Lamb-665429450.Sad_Trombone-Joe_Lamb-665429450"));
	Sound2 = Soundf.Object;
}


void ASimonSaysBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// HUD creation
	if (HUDWidget) {
		pHUDWidget = CreateWidget <UUserWidget>(GetGameInstance(), HUDWidget);
		if (pHUDWidget) {
			pHUDWidget->AddToViewport();
			pHUDWidget->SetVisibility(ESlateVisibility::Visible);
			pHUDScore = (UTextBlock*) pHUDWidget->GetWidgetFromName("ScoreText");
			pHUDText = (UTextBlock*) pHUDWidget->GetWidgetFromName("TextBlock_90");

		}
	}

	if (RecordsWidget) {
		pRecordsWidget = CreateWidget <UUserWidget>(GetGameInstance(), RecordsWidget);
		if (pRecordsWidget) {
			pRecordsScore = (UTextBlock*)pRecordsWidget->GetWidgetFromName("TextScore");
			pRecordsName = (UTextBlock*)pRecordsWidget->GetWidgetFromName("TextName");
			pRecordsIndex = (UTextBlock*)pRecordsWidget->GetWidgetFromName("IndexText");
		}
	}


	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = ((BlockIndex%Size) * BlockSpacing); // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset * 1.5f, YOffset * 1.5f, 0.f) + GetActorLocation();
		// Spawn a block

		
		if (BlockIndex == 0) {
			RedBlock = GetWorld()->SpawnActor<ARedBlock>(BlockLocation, FRotator(0, 0, 0));
			// Tell the block about its owner
			if (RedBlock != nullptr)
			{
				RedBlock->OwningGrid = this;

			}
		}
		else if (BlockIndex == 1) {
			GreenBlock = GetWorld()->SpawnActor<AGreenBlock>(BlockLocation, FRotator(0, 0, 0));
			// Tell the block about its owner
			if (GreenBlock != nullptr)
			{
				GreenBlock->OwningGrid = this;
			}
		}
		else if (BlockIndex == 2) {
			BlueBlock = GetWorld()->SpawnActor<ABlueBlock>(BlockLocation, FRotator(0, 0, 0));
			// Tell the block about its owner
			if (BlueBlock != nullptr)
			{
				BlueBlock->OwningGrid = this;
			}
		}else if ( BlockIndex == 3){
			YellowBlock = GetWorld()->SpawnActor<AYellowBlock>(BlockLocation, FRotator(0, 0, 0));
			// Tell the block about its owner
			if (YellowBlock != nullptr)
			{
				YellowBlock->OwningGrid = this;
			}
		}
	}

	// Filling the block array
	BlockArray.Add(BlueBlock);
	BlockArray.Add(RedBlock);
	BlockArray.Add(GreenBlock);
	BlockArray.Add(YellowBlock);

	// Generates the first block of the sequence
	GetRandBlock();

	

}

void ASimonSaysBlockGrid::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	AccumulatedDeltaTime += DeltaSeconds;
	InitialTimer += DeltaSeconds;
	if (InitialTimer > 2.0f) {
		if (IsPlaying()) {
			
			GetSequence();
		}
		else {
			ChangeText("PLAYER TURN");
		}
	}
}

void ASimonSaysBlockGrid::ChangeText(FString text) {
	if (pHUDText.IsValid()) {
		pHUDText->SetText(FText::FromString(text));
	}

}


void ASimonSaysBlockGrid::AddScore()
{
	// Increment score
	if (pHUDScore.IsValid()) {
		Score += 15;
		pHUDScore->SetText(FText::FromString(FString::FromInt(Score)));
		
	}
}

int ASimonSaysBlockGrid::GetScore() {
	return Score;
}

void ASimonSaysBlockGrid::GetRandBlock() {
	Rand = FMath::RandRange(0, 3);
	ASimonSaysBlock* Block = BlockArray[Rand];
	SequenceArray.Add(Block->GetId());
	
}

void ASimonSaysBlockGrid::SetPlay(bool play) {
	Playing = play;
}

bool ASimonSaysBlockGrid::IsPlaying() {
	return Playing;
}

void ASimonSaysBlockGrid::GetSequence() {
	if (AccumulatedDeltaTime > 1.5f) {
		ChangeText("SIMON TURN");
		int aux = SequenceArray[Pos];
		ASimonSaysBlock* AuxBlock = BlockArray[aux];
		AuxBlock->SwitchOn(1.0f);
		AuxBlock->PlaySound();
		AccumulatedDeltaTime = 0.0f;
		Pos++;
		if (SequenceArray.Num() == Pos) {
			Pos = 0;
			SetPlay(false);
		}
		
	}
}

void ASimonSaysBlockGrid::Save(){
	PlayerName = TEXT("PlayerOne");
	USaveGameSimonSays* SaveGameInstance = Cast<USaveGameSimonSays>(UGameplayStatics::CreateSaveGameObject(USaveGameSimonSays::StaticClass()));
	SaveGameInstance->PlayerName = PlayerName;
	SaveGameInstance->Score = Score;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	
}
	
void ASimonSaysBlockGrid::Load() {
	USaveGameSimonSays* LoadGameInstance = Cast<USaveGameSimonSays>(UGameplayStatics::CreateSaveGameObject(USaveGameSimonSays::StaticClass()));
	LoadGameInstance = Cast<USaveGameSimonSays>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	FString PlayerNameToDisplay = LoadGameInstance->PlayerName;
	int ScoreDisplay = LoadGameInstance->Score;

	pRecordsScore->SetText(FText::FromString(FString::FromInt(ScoreDisplay)));
	pRecordsName->SetText(FText::FromString(PlayerNameToDisplay));
	
}



void ASimonSaysBlockGrid::CheckSequence(int id) {
	if (SequenceArray[Pos] == id) {
		Pos++;
		if (SequenceArray.Num() == Pos) {
			AddScore();
			Pos = 0;
			GetRandBlock();
			AccumulatedDeltaTime = 0.0f;
			SetPlay(true);
			return;
		}
		
		return;
	}
	else {
		
		UGameplayStatics::PlaySound2D(GetWorld(), Sound2, 1.0f, 1.0f, 0.0f, nullptr);
		//Mostrar fin juego
		
//		Save();

		
		SetPlay(false);
		UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("RecordsMap")));

		//Load();
	}
}
#undef LOCTEXT_NAMESPACE
