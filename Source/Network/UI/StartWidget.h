// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UButton* mStartButton;
	UButton* mEndButton;

protected:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void StartButtonClick();

	UFUNCTION()
	void EndButtonClick();
};
