// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimonSaysBlock.generated.h"

/** A block that can be clicked */
UCLASS(Abstract)
class ASimonSaysBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	ASimonSaysBlock();

	/** Are we currently active? */
	bool bIsActive;

	int Id;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	/** Pointer to orange material used on active blocks */
	UPROPERTY()
	class UMaterialInstance* YellowMaterial;

	UPROPERTY()
	class UMaterialInstance* GreenMaterial;

	UPROPERTY()
	class UMaterialInstance* RedMaterial;


	/** Grid that owns us */
	UPROPERTY()
	class ASimonSaysBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	virtual void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	virtual void HandleClicked();

	virtual void Highlight(bool bOn);

	virtual void SetId(int id);

	virtual int GetId();

	virtual void PlaySound();

	virtual void Tick(float DeltaSeconds) override;
	
	float AccumulatedDeltaTime;

	virtual void SwitchOn(float timer);

	virtual void SwitchOff();

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }

	
};



