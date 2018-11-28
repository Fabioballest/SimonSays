// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonSaysPawn.h"
#include "SimonSaysBlock.h"
#include "RedBlock.h"
#include "BlueBlock.h"
#include "YellowBlock.h"
#include "GreenBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ASimonSaysPawn::ASimonSaysPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ASimonSaysPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
		}
	}
}

void ASimonSaysPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &ASimonSaysPawn::TriggerClick);
}

void ASimonSaysPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}


void ASimonSaysPawn::TriggerClick()
{
	if (CurrentBlockFocus)
	{
		CurrentBlockFocus->HandleClicked();
	}
}

void ASimonSaysPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		
		if (HitResult.Actor.Get()->IsA(AYellowBlock::StaticClass())) {
			AYellowBlock* HitBlock = Cast<AYellowBlock>(HitResult.Actor.Get());
			if (CurrentBlockFocus != HitBlock)
			{
				if (CurrentBlockFocus)
				{
					CurrentBlockFocus->Highlight(false);
				}
				if (HitBlock)
				{
					HitBlock->Highlight(true);
				}
				CurrentBlockFocus = HitBlock;
			}
		}
		else if (HitResult.Actor.Get()->IsA(ARedBlock::StaticClass())) {
			ARedBlock* HitBlock = Cast<ARedBlock>(HitResult.Actor.Get());
			if (CurrentBlockFocus != HitBlock)
			{
				if (CurrentBlockFocus)
				{
					CurrentBlockFocus->Highlight(false);
				}
				if (HitBlock)
				{
					HitBlock->Highlight(true);
				}
				CurrentBlockFocus = HitBlock;
			}
		}
		else if (HitResult.Actor.Get()->IsA(ABlueBlock::StaticClass())) {
			ABlueBlock* HitBlock = Cast<ABlueBlock>(HitResult.Actor.Get());
			if (CurrentBlockFocus != HitBlock)
			{
				if (CurrentBlockFocus)
				{
					CurrentBlockFocus->Highlight(false);
				}
				if (HitBlock)
				{
					HitBlock->Highlight(true);
				}
				CurrentBlockFocus = HitBlock;
			}
		}
		else if (HitResult.Actor.Get()->IsA(AGreenBlock::StaticClass())) {
			AGreenBlock* HitBlock = Cast<AGreenBlock>(HitResult.Actor.Get());
			if (CurrentBlockFocus != HitBlock)
			{
				if (CurrentBlockFocus)
				{
					CurrentBlockFocus->Highlight(false);
				}
				if (HitBlock)
				{
					HitBlock->Highlight(true);
				}
				CurrentBlockFocus = HitBlock;
			}
		}
			
		
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}