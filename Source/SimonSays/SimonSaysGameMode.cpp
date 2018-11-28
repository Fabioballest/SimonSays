// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonSaysGameMode.h"
#include "SimonSaysPlayerController.h"
#include "SimonSaysPawn.h"

ASimonSaysGameMode::ASimonSaysGameMode()
{
	// no pawn by default
	DefaultPawnClass = ASimonSaysPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ASimonSaysPlayerController::StaticClass();
}
