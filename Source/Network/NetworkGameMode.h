// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkGameMode.generated.h"

UCLASS(minimalapi)
class ANetworkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANetworkGameMode();

protected:
	int32		mItemCount = 9;
	int32		mTeamNumber = 0;

public:
	void PickUpItem()
	{
		--mItemCount;

		UE_LOG(Network, Warning, TEXT("Item Count : %d"), mItemCount);
	}

protected:
	virtual void BeginPlay();

public:
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole,
		const FString& Portal, const FString& Options,
		const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
};



