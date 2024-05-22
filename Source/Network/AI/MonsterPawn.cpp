// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"
#include "MonsterAnimInstance.h"

AMonsterPawn::AMonsterPawn()
{
	mState = CreateDefaultSubobject<UAIState>(TEXT("AIState"));
}

//
//void AMonsterPawn::ChangeAnim_Implementation(uint8 AnimType)
//{
//	//mAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
//	mMonsterAnimType = (EMonsterAnimType)AnimType;
//
//	mAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
//
//	UE_LOG(Network, Warning, TEXT("ChangeAnimType"));
//	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("ChangeAnimType"));
//}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

	mMonsterAnimInst = Cast<UMonsterAnimInstance>(mMesh->GetAnimInstance());
}

void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterPawn::EnableAttack(bool Enable, EAttackCollider Type)
{
}
