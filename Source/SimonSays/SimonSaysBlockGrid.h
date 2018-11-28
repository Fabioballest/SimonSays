// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimonSaysBlock.h"
#include "GameFramework/Actor.h"
#include "SimonSaysBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class ASimonSaysBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;


public:
	ASimonSaysBlockGrid();

	/** How many blocks have been clicked */
	int Score;

	virtual void Tick(float DeltaSeconds) override;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	class ARedBlock* RedBlock;

	class AGreenBlock* GreenBlock;

	class ABlueBlock* BlueBlock;
		
	class AYellowBlock* YellowBlock;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore();

	UFUNCTION(BlueprintCallable, Category = "Text")
		void ChangeText(FString text);

	int GetScore();

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	
	float AccumulatedDeltaTime;

	float InitialTimer;

	void GetRandBlock();

	TArray<ASimonSaysBlock*> BlockArray;

	TArray<int32> SequenceArray;

	void SetPlay(bool play);

	bool Playing = true;

	int32 Rand;

	int Pos = 0;

	bool IsPlaying();

	void GetSequence();

	void CheckSequence(int id);

	USoundBase* Sound2;

	FString PlayerName;

	void Save();

	void Load();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> HUDWidget;
	
		UUserWidget* pHUDWidget;
	
		TWeakObjectPtr<class UTextBlock> pHUDScore;

		TWeakObjectPtr<class UTextBlock> pHUDText;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Records")
			TSubclassOf<class UUserWidget> RecordsWidget;

		UUserWidget* pRecordsWidget;

		TWeakObjectPtr<class UTextBlock> pRecordsScore;

		TWeakObjectPtr<class UTextBlock> pRecordsName;

		TWeakObjectPtr<class UTextBlock> pRecordsIndex;


		
		
};