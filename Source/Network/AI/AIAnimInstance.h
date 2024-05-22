// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAIAnimInstance();

public:
	virtual void ChangeAnim(uint8 AnimType);

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
