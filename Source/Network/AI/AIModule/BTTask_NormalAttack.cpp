// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalAttack.h"
#include "../MonsterPawn.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"
#include "../AIState.h"

UBTTask_NormalAttack::UBTTask_NormalAttack()
{
	NodeName = TEXT("NormalAttack");

	// Tick 함수 호출이 가능하게 한다.
	bNotifyTick = true;

	// OnTaskFinished 이벤트를 사용할 수 있게 한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	// 위에서 얻어온 AIController가 빙의되어 있는 Pawn을 얻어온다.
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return EBTNodeResult::Failed;

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		// 이동을 멈추게 한다.
		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	// 애니메이션을 Attack 으로 변경한다.
	Pawn->ChangeAnimType((uint8)EMonsterAnimType::Attack);

	return EBTNodeResult::InProgress;
}

void UBTTask_NormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	// 위에서 얻어온 AIController가 빙의되어 있는 Pawn을 얻어온다.
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
	{
		// Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		// Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAnimType((uint8)EMonsterAnimType::Idle);

		return;
	}

	if (Pawn->IsAttackEnd())
	{
		Pawn->SetAttackEnd(false);

		// AI가 Target을 바라보게 회전시킨다.
		// AI의 위치와 Target의 위치를 얻어온다.
		FVector	AILocation = Pawn->GetActorLocation();
		FVector	TargetLocation = Target->GetActorLocation();

		// AI가 Target을 바라보는 방향을 구한다.
		FVector	Dir = TargetLocation - AILocation;
		Dir.Z = 0.0;

		// 두 위치 사이의 거리를 구한다.
		AILocation.Z -= Pawn->GetHalfHeight();

		// Target의 RootComponent를 CapsuleComponent로 변환한다.
		UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

		if (IsValid(TargetCapsule))
		{
			TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();
		}

		float	Distance = FVector::Distance(AILocation, TargetLocation);

		//UAIState* State = Pawn->GetState<UAIState>();

		// 공격 거리를 빠져나갔을 경우
		if (Distance > 200.f)
		{
			// Task를 종료한다.
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

			// 애니메이션을 Idle 로 변경한다.
			Pawn->ChangeAnimType((uint8)EMonsterAnimType::Idle);
		}

		// 공격 거리 안쪽일 경우
		else
		{
			FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
			Rot.Pitch = 0.0;
			Rot.Roll = 0.0;

			Pawn->SetActorRotation(Rot);
		}
	}
}

