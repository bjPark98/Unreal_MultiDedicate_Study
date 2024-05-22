// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameStateBase.h"
#include "NetworkGameState.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ANetworkGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ANetworkGameState();

protected:
	// Replicated : 리플리케이트 시켜준다.
	// ReplicatedUsing : RepNotify 기능이다. = 함수이름을 작성해주어야 한다.
	UPROPERTY(Replicated)
	int32	mItemCount = 9;

	UPROPERTY(ReplicatedUsing=OnRep_Team1Change)
	int32	mTeam1Count = 0;

	UPROPERTY(ReplicatedUsing = OnRep_Team2Change)
	int32	mTeam2Count = 0;

public:
	UFUNCTION()
	void OnRep_Team1Change();

	UFUNCTION()
	void OnRep_Team2Change();

public:
	// Server : 서버 용도.
	// Client : 클라이언트 용도.
	// NetMulticast : 서버, 클라이언트
	// Reliable : 원격 머신에서 확실하게 실행될 수 있게 해준다.
	UFUNCTION(Server, Reliable)
	void PickUpItem();
	void PickUpItem_Implementation();


	UFUNCTION(Server, Reliable)
	void AddTeamItem(bool Team1);
	void AddTeamItem_Implementation(bool Team1);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
