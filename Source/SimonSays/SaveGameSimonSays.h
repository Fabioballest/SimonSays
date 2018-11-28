// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameSimonSays.generated.h"

/**
 * 
 */
UCLASS()
class SIMONSAYS_API USaveGameSimonSays : public USaveGame
{
	GENERATED_BODY()
	

public:
	USaveGameSimonSays();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int Score;
};
