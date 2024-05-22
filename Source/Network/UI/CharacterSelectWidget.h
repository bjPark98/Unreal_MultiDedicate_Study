// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UButton* mStartButton;
	UButton* mCreateButton;
	UEditableTextBox* mInputName;

protected:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void StartButtonClick();

	UFUNCTION()
	void CreateButtonClick();
};
