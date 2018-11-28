// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimonSaysBlock.h"
#include "RedBlock.generated.h"

/**
 * 
 */
UCLASS()
class SIMONSAYS_API ARedBlock : public ASimonSaysBlock
{
	GENERATED_BODY()
	
	

public:
	ARedBlock();

	int Id;

	float AccumulatedDeltaTime;

	float TimeBetweenBlock;
	
	UFUNCTION()
		virtual void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	virtual void HandleClicked();

	virtual void Highlight(bool bOn);

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetId(int id);

	virtual int GetId();

	void SwitchOn(float timer);

	void SwitchOff();

	void PlaySound();

	USoundBase* Sound;
};
