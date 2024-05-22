// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStartPlayerController();

protected:
	TSubclassOf<UUserWidget>	mUIClass;
	UUserWidget* mUIWidget;

protected:
	virtual void BeginPlay();
};
