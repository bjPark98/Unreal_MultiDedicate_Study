// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterPawn.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
}

void UMonsterAnimInstance::ChangeAnim(uint8 AnimType)
{
	mAnimType = (EMonsterAnimType)AnimType;
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mAnimType = EMonsterAnimType::Idle;
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonsterAnimInstance::AnimNotify_EnableAttack()
{
	AMonsterPawn* Monster = Cast<AMonsterPawn>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->EnableAttack(true, EAttackCollider::Right);
}

void UMonsterAnimInstance::AnimNotify_DisableAttack()
{
	AMonsterPawn* Monster = Cast<AMonsterPawn>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->EnableAttack(false, EAttackCollider::Right);
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AMonsterPawn* Monster = Cast<AMonsterPawn>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->SetAttackEnd(true);
}

void UMonsterAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 리플리케이트 되는 모든 변수들을 여기에 등록한다.
	// DOREPLIFETIME은 현재 클래스 타입, 변수이름을 작성한다.
	DOREPLIFETIME(UMonsterAnimInstance, mAnimType);
}


