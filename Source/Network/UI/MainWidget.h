// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	class UAIHUDWidget* mAIHUD;
	class UChatWidget* mChatWidget;

protected:
	virtual void NativeConstruct();

public:
	void SetAIName(const FString& Name);
	void SetAIHP(float HPPercent);

	void SetChatNormal(const FString& ChatMsg);

	// UI를 활성화한다.
};
