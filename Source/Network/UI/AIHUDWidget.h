// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "AIHUDWidget.generated.h"


DECLARE_MULTICAST_DELEGATE(FConstructDelegate)


UCLASS()
class NETWORK_API UAIHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UTextBlock* mNameText;
	UProgressBar* mHPBar;

	FConstructDelegate	mConstructDelegate;

protected:
	virtual void NativeConstruct();

public:
	void SetAIName(const FString& Name);
	void SetAIHP(float HPPercent);

	template <typename T>
	void AddConstructDelegate(T* Obj, void(T::* Func)())
	{
		mConstructDelegate.AddUObject(Obj, Func);
	}
};
