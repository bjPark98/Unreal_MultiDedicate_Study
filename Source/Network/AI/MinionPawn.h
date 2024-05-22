// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterPawn.h"
#include "MinionPawn.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API AMinionPawn : public AMonsterPawn
{
	GENERATED_BODY()

public:
	AMinionPawn();

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mSwordL;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mSwordR;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EnableAttack(bool Enable, EAttackCollider Type);

	UFUNCTION()
	void AttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
