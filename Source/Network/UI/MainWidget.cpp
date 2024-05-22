// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "AIHUDWidget.h"
#include "ChatWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mAIHUD = Cast<UAIHUDWidget>(GetWidgetFromName(TEXT("UI_AIHUD")));
	mChatWidget = Cast<UChatWidget>(GetWidgetFromName(TEXT("UI_Chat")));
}

void UMainWidget::SetAIName(const FString& Name)
{
	mAIHUD->SetAIName(Name);
}

void UMainWidget::SetAIHP(float HPPercent)
{
	mAIHUD->SetAIHP(HPPercent);
}

void UMainWidget::SetChatNormal(const FString& ChatMsg)
{
	mChatWidget->SetChatNormal(ChatMsg);
}
