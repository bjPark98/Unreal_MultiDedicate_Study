// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoginGameMode();

private:
	class CPacketQueue* mQueue;

public:
	virtual void InitGame(const FString& MapName, const FString& Options,
		FString& ErrorMessage);

	virtual void Tick(float DeltaTime) override;
};
