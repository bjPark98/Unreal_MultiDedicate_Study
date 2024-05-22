// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "NetworkPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ANetworkPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANetworkPlayerController();
	
protected:
	TSubclassOf<class UMainWidget>	mMainWidgetClass;
	class UMainWidget* mMainWidget;
	class CPacketQueue* mQueue = nullptr;

	UPROPERTY(Replicated)
	int32	mTeamNumber;

protected:
	// To add mapping context
	virtual void BeginPlay();
	virtual void OnPossess(APawn* aPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(Server, Reliable)
	void SetTeamNumber(int Number);
	void SetTeamNumber_Implementation(int Number);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
