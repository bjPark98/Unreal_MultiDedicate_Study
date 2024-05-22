// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPlayerController.h"
#include "../../UI/StartWidget.h"

AStartPlayerController::AStartPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>	UIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Start.UI_Start_C'"));

	if (UIClass.Succeeded())
		mUIClass = UIClass.Class;

	bShowMouseCursor = true;
}

void AStartPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);

	if (IsValid(mUIClass))
	{
		mUIWidget = CreateWidget<UStartWidget>(GetWorld(), mUIClass);
		mUIWidget->AddToViewport();
	}
}
