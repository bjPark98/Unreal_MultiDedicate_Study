// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class NETWORK_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* mMovement;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* mHPWidget;

	class UAIHUDWidget* mHPBar;

	UPROPERTY(EditAnywhere)
	class UAIState* mState = nullptr;

	class AAISpawnPoint* mSpawnPoint;

	class UAIAnimInstance* mAnimInst;

	bool	mAttackEnd = false;

public:
	void SetSpawnPoint(class AAISpawnPoint* Point)
	{
		mSpawnPoint = Point;
	}

	float GetHalfHeight()	const
	{
		return mCapsule->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius()
	{
		return mCapsule->GetScaledCapsuleRadius();
	}

	void SetAttackEnd(bool End)
	{
		mAttackEnd = End;
	}

	bool IsAttackEnd()
	{
		return mAttackEnd;
	}

public:
	UFUNCTION(NetMulticast, Reliable)
	void ChangeAnimType(uint8 AnimType);
	void ChangeAnimType_Implementation(uint8 AnimType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);


private:
	UFUNCTION()
	void HPCallback();

public:
	UFUNCTION(NetMulticast, Reliable)
	void AddUIHP(float HPPercent);
	void AddUIHP_Implementation(float HPPercent);
};
