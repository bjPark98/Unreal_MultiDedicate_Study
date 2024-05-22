// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectGameMode.h"
#include "../Player/CharacterSelect/CharacterSelectPlayerController.h"
#include "../Player/CharacterSelect/SelectPawn.h"

ASelectGameMode::ASelectGameMode()
{
	PlayerControllerClass = ACharacterSelectPlayerController::StaticClass();
	//DefaultPawnClass = ASelectPawn::StaticClass();
	DefaultPawnClass = nullptr;
}


