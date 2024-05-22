// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "LoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALoginPlayerController();

protected:
	TSubclassOf<UUserWidget>	mUIClass;
	UUserWidget* mUIWidget;

protected:
	virtual void BeginPlay();
};
