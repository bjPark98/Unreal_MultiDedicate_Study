// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death
};

UCLASS()
class NETWORK_API UMonsterAnimInstance : public UAIAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	EMonsterAnimType	mAnimType;

public:
	void ChangeAnim(uint8 AnimType);

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_EnableAttack();

	UFUNCTION()
	void AnimNotify_DisableAttack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
