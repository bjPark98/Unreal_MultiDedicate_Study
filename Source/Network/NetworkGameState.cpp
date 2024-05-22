// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameState.h"

ANetworkGameState::ANetworkGameState()
{
}

void ANetworkGameState::OnRep_Team1Change()
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("Team1Change"));
}

void ANetworkGameState::OnRep_Team2Change()
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("Team2Change"));
}

void ANetworkGameState::PickUpItem_Implementation()
{
	--mItemCount;

	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("PickUp"));
	UE_LOG(Network, Warning, TEXT("PickUp"));
}

void ANetworkGameState::AddTeamItem_Implementation(bool Team1)
{
	if (Team1)
		++mTeam1Count;

	else
		++mTeam2Count;
}

void ANetworkGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ANetworkGameState::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 리플리케이트 되는 모든 변수들을 여기에 등록한다.
	// DOREPLIFETIME은 현재 클래스 타입, 변수이름을 작성한다.
	DOREPLIFETIME(ANetworkGameState, mItemCount);
	DOREPLIFETIME(ANetworkGameState, mTeam1Count);
	DOREPLIFETIME(ANetworkGameState, mTeam2Count);
}
