// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SelectCharacter.generated.h"

UCLASS()
class NETWORK_API ASelectCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere)
	EPlayerJob	mJob;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
