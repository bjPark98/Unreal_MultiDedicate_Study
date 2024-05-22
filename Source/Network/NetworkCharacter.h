// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NetworkCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ANetworkCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	int32	mTeamNumber;

	static UParticleSystem* mHitParticle;
	static USoundBase* mHitSound;

public:
	void SetTeamNumber(int32 TeamNumber)
	{
		mTeamNumber = TeamNumber;
	}

protected:
	UPROPERTY(Replicated)
	FString		mName;

	UPROPERTY(Replicated)
	int32		mAttack = 50;

	UPROPERTY(Replicated)
	int32		mDefense = 20;

	UPROPERTY(Replicated)
	int32		mHP = 500;

	UPROPERTY(Replicated)
	int32		mHPMax = 500;

	UPROPERTY(Replicated)
	int32		mMP = 100;

	UPROPERTY(Replicated)
	int32		mMPMax = 100;

public:
	FString GetAIName()
	{
		return mName;
	}

	int32 GetAttack()
	{
		return mAttack;
	}

	int32 GetDefense()
	{
		return mDefense;
	}

	int32 GetHP()
	{
		return mHP;
	}

	int32 GetHPMax()
	{
		return mHPMax;
	}

public:
	ANetworkCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void NormalAttack(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION(Server, Reliable)
	void AttackCheck();
	void AttackCheck_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void AttackEffect(const FVector& Location);
	void AttackEffect_Implementation(const FVector& Location);

	UFUNCTION(Client, Reliable)
	void AttackDebugDraw(bool IsCollision, const FVector& Start, const FVector& End);
	void AttackDebugDraw_Implementation(bool IsCollision, const FVector& Start, 
		const FVector& End);

	UFUNCTION(NetMulticast, Reliable)
	void AddHP(float HP);
	void AddHP_Implementation(float HP);
};

