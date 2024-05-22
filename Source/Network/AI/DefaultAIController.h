// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADefaultAIController();

protected:
	UBehaviorTree* mBehaviourTree;
	UBlackboardData* mBlackboard;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* mAIPerception;

	UAISenseConfig_Sight* mSightConfig;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnTargetDetect(AActor* Target, FAIStimulus const Stimulus);
};
