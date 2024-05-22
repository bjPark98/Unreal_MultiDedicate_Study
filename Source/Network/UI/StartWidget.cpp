// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mEndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));

	mStartButton->OnClicked.AddDynamic(this, &UStartWidget::StartButtonClick);
	mEndButton->OnClicked.AddDynamic(this, &UStartWidget::EndButtonClick);
}

void UStartWidget::StartButtonClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Click"));
	
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("127.0.0.1:10000"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Login"));
}

void UStartWidget::EndButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(),
		EQuitPreference::Quit, true);
}
