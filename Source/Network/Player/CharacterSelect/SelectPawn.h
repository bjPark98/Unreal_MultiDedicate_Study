// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "SelectPawn.generated.h"

UENUM(BlueprintType)
enum class ECameraTargetTransitionType : uint8
{
	VTBlend_Linear,
	/** Camera has a slight ease in and ease out, but amount of ease cannot be tweaked. */
	VTBlend_Cubic,
	/** Camera immediately accelerates, but smoothly decelerates into the target.  Ease amount controlled by BlendExp. */
	VTBlend_EaseIn,
	/** Camera smoothly accelerates, but does not decelerate into the target.  Ease amount controlled by BlendExp. */
	VTBlend_EaseOut,
	/** Camera smoothly accelerates and decelerates.  Ease amount controlled by BlendExp. */
	VTBlend_EaseInOut,
	/** The game's camera system has already performed the blending. Engine should not blend at all */
	VTBlend_PreBlended,
	VTBlend_MAX
};

UCLASS()
class NETWORK_API ASelectPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectPawn();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	UPROPERTY(EditAnywhere)
	AActor* mCreateCamera;

	UPROPERTY(EditAnywhere)
	float	mCreateCameraBlendTime = 1.f;

	UPROPERTY(EditAnywhere)
	ECameraTargetTransitionType	mCreateCameraTransitionFunction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void CreateCameraTransition();
	void ReturnCameraTransition();
};
