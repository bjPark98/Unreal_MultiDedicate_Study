// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "MonsterAnimInstance.h"
#include "MonsterPawn.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API AMonsterPawn : public AAIPawn
{
	GENERATED_BODY()

public:
	AMonsterPawn();

protected:
	class UMonsterAnimInstance* mMonsterAnimInst;

	UPROPERTY(EditAnywhere)
	EMonsterAnimType	mMonsterAnimType = EMonsterAnimType::Idle;

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EnableAttack(bool Enable, EAttackCollider Type);
};
