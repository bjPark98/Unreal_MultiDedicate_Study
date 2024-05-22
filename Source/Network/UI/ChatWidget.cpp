// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"
#include "../Network/NetworkManager.h"
#include "Components/TextBlock.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mChatScroll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ChatScroll")));
	mChatInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChatInput")));
	mSendButton = Cast<UButton>(GetWidgetFromName(TEXT("SendButton")));

	mSendButton->OnClicked.AddDynamic(this, &UChatWidget::ChatSend);

	mChatInput->OnTextCommitted.AddDynamic(this, &UChatWidget::ChatCommit);
}

void UChatWidget::ChatSend()
{
	mChatMsg = mChatInput->GetText().ToString();

	int32	Length = mChatMsg.Len() * 2;

	uint8	ChatMsg[1024] = {};

	FMemory::Memcpy(ChatMsg, *mChatMsg, Length);

	CNetworkManager::GetInst()->Send(TEXT("ChatSession"), EChatType::Normal,
		Length, ChatMsg);
}

void UChatWidget::ChatCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		ChatSend();

		mChatInput->SetText(FText::GetEmpty());
	}
}

void UChatWidget::SetChatNormal(const FString& ChatMsg)
{
	UTextBlock* NewText = NewObject<UTextBlock>(mChatScroll);

	NewText->SetText(FText::FromString(ChatMsg));

	mChatScroll->AddChild(NewText);
	mChatScroll->ScrollToEnd();
}
