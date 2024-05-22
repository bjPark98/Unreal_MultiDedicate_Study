// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPlayerController.h"
#include "../../UI/LoginWidget.h"

ALoginPlayerController::ALoginPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>	UIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Login.UI_Login_C'"));

	if (UIClass.Succeeded())
		mUIClass = UIClass.Class;

	bShowMouseCursor = true;
}

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);

	if (IsValid(mUIClass))
	{
		mUIWidget = CreateWidget<ULoginWidget>(GetWorld(), mUIClass);
		mUIWidget->AddToViewport();
	}
}
