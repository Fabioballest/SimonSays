// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimonSaysBlock.h"
#include "YellowBlock.generated.h"

/**
*
*/
UCLASS()
class SIMONSAYS_API AYellowBlock : public ASimonSaysBlock
{
	GENERATED_BODY()

	
public:
	AYellowBlock();

	int Id;

	float AccumulatedDeltaTime;

	float TimeBetweenBlock;

	UFUNCTION()
		virtual void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	virtual void HandleClicked();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Highlight(bool bOn);

	void SwitchOn(float timer);

	void SwitchOff();

	virtual void SetId(int id);

	virtual int GetId();

	void PlaySound();

	USoundBase* Sound;
};
