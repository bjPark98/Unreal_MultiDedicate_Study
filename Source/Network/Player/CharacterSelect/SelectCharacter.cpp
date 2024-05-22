// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacter.h"

// Sets default values
ASelectCharacter::ASelectCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mMesh->SetupAttachment(mCapsule);

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mCapsule->SetCollisionProfileName(TEXT("Player"));

	SetRootComponent(mCapsule);
}

// Called when the game starts or when spawned
void ASelectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

