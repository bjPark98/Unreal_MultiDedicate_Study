// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AIState.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETWORK_API UAIState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIState();

protected:
	FString		mName = TEXT("Minion");
	int32		mAttack = 30;
	int32		mDefense = 10;

	UPROPERTY(Replicated)
	int32		mHP = 100;

	int32		mHPMax = 100;
	int32		mMP = 10;
	int32		mMPMax = 10;

public:
	FString GetAIName()
	{
		return mName;
	}

	int32 GetAttack()
	{
		return mAttack;
	}

	int32 GetDefense()
	{
		return mDefense;
	}

	int32 GetHP()
	{
		return mHP;
	}

	int32 GetHPMax()
	{
		return mHPMax;
	}

	void AddHP(float Damage)
	{
		mHP += Damage;

		if (mHP < 0)
			mHP = 0;

		UE_LOG(Network, Warning, TEXT("HP : %d"), mHP);
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
