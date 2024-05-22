// Fill out your copyright notice in the Description page of Project Settings.


#include "AIHUDWidget.h"


void UAIHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	// 함수가 등록되어 있는지를 판단하여 등록된 모든 함수를 호출한다.
	if (mConstructDelegate.IsBound())
		mConstructDelegate.Broadcast();
}

void UAIHUDWidget::SetAIName(const FString& Name)
{
	mNameText->SetText(FText::FromString(Name));
}

void UAIHUDWidget::SetAIHP(float HPPercent)
{
	mHPBar->SetPercent(HPPercent);
}
