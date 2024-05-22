// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
#include "../Player/CharacterSelect/SelectPawn.h"

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mCreateButton = Cast<UButton>(GetWidgetFromName(TEXT("CreateButton")));
	mInputName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputName")));

	mStartButton->OnClicked.AddDynamic(this, 
		&UCharacterSelectWidget::StartButtonClick);

	mCreateButton->OnClicked.AddDynamic(this,
		&UCharacterSelectWidget::CreateButtonClick);
}

void UCharacterSelectWidget::StartButtonClick()
{
	if (mInputName->GetText().IsEmpty())
		return;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Click"));

	// 옵션을 이용해서 데이터를 넘겨줄때 ?를 이용해서 여러 데이터를 구분할 수 있다.
	// FString Option = FString::Printf(TEXT("InputName=%s?PlayerJob=%d"), 이름, 직업);

	FString	InputName = mInputName->GetText().ToString();

	FString	Option = FString::Printf(TEXT("InputName=%s"), *InputName);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("127.0.0.1:10001"), true,
		Option);
}

void UCharacterSelectWidget::CreateButtonClick()
{
	GetOwningPlayerPawn<ASelectPawn>()->CreateCameraTransition();
}
