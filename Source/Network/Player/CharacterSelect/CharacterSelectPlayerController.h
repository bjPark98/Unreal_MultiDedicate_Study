// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "CharacterSelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ACharacterSelectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterSelectPlayerController();

protected:
	TSubclassOf<UUserWidget>	mUIClass;
	UUserWidget* mUIWidget;

protected:
	virtual void BeginPlay();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
