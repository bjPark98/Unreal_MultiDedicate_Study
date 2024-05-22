// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"

// Sets default values
ASelectPawn::ASelectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SetRootComponent(mRoot);

	mCamera->SetupAttachment(mRoot);
}

// Called when the game starts or when spawned
void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASelectPawn::CreateCameraTransition()
{
	EViewTargetBlendFunction	Func = (EViewTargetBlendFunction)mCreateCameraTransitionFunction;

	GetController<APlayerController>()->SetViewTargetWithBlend(mCreateCamera,
		mCreateCameraBlendTime, Func);

	// 현재 ViewTarget을 얻어온다.
	//GetController<APlayerController>()->GetViewTarget()
	//FViewTargetTransitionParams	param;
	//GetController<APlayerController>()->SetViewTarget(mCreateCamera, param);
}

void ASelectPawn::ReturnCameraTransition()
{
	EViewTargetBlendFunction	Func = (EViewTargetBlendFunction)mCreateCameraTransitionFunction;

	GetController<APlayerController>()->SetViewTargetWithBlend(this,
		mCreateCameraBlendTime, Func);
}

