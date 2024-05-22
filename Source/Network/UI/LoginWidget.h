// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UButton* mLoginButton;
	UEditableTextBox* mIDText;
	UEditableTextBox* mPasswordText;

protected:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void LoginButtonClick();
};
