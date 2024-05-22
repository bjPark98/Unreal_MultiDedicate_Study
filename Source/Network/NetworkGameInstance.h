// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "NetworkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UNetworkGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNetworkGameInstance();
	
public:
	virtual void Init();
	virtual void FinishDestroy() override;
};
