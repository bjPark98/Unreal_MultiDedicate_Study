// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UScrollBox* mChatScroll;
	UEditableTextBox* mChatInput;
	UButton* mSendButton;

	FString	mChatMsg;

protected:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void ChatSend();

	UFUNCTION()
	void ChatCommit(const FText& Text, ETextCommit::Type CommitMethod);

	void SetChatNormal(const FString& ChatMsg);
};
