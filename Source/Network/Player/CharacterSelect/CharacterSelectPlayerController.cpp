// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectPlayerController.h"
#include "../../UI/CharacterSelectWidget.h"

ACharacterSelectPlayerController::ACharacterSelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>	UIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_CharacterSelect.UI_CharacterSelect_C'"));

	if (UIClass.Succeeded())
		mUIClass = UIClass.Class;

	bShowMouseCursor = true;
}

void ACharacterSelectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);

	if (IsValid(mUIClass))
	{
		mUIWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), mUIClass);
		mUIWidget->AddToViewport();
	}
}

void ACharacterSelectPlayerController::Tick(float DeltaTime)
{
	FHitResult	result;

	bool	Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3,
		false, result);

	if (Hit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			TEXT("Mouse Hit"));
	}
}


