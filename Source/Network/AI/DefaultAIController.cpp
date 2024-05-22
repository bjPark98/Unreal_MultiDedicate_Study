// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"

ADefaultAIController::ADefaultAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_Minion.BT_Minion'"));

	if (AITree.Succeeded())
		mBehaviourTree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>	Data(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_Monster.BB_Monster'"));

	if (Data.Succeeded())
		mBlackboard = Data.Object;

	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");

	mAIPerception->bEditableWhenInherited = true;

	// AIPerception 등록
	SetPerceptionComponent(*mAIPerception);

	// 시야 감지 추가
	mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	mSightConfig->SightRadius = 700.f;
	mSightConfig->LoseSightRadius = mSightConfig->SightRadius + 150.f;
	mSightConfig->PeripheralVisionAngleDegrees = 90.f;
	mSightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;
	mSightConfig->SetMaxAge(0.f);

	mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// AIPerception에 Sight 를 등록한다.
	mAIPerception->ConfigureSense(*mSightConfig);

	// 대표 감각을 설정한다.
	mAIPerception->SetDominantSense(mSightConfig->GetSenseImplementation());
}

void ADefaultAIController::BeginPlay()
{
	Super::BeginPlay();

	mAIPerception->OnTargetPerceptionUpdated.AddDynamic(this,
		&ADefaultAIController::OnTargetDetect);
}

void ADefaultAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADefaultAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 블랙보드가 있을 경우
	if (mBlackboard)
	{
		// AI 컨트롤러가 가지고 있는 Blackboard 컴포넌트에 읽어온 블랙보드를 지정한다.
		UBlackboardComponent* BlackboardRef = Blackboard;

		if (UseBlackboard(mBlackboard, BlackboardRef))
		{
			RunBehaviorTree(mBehaviourTree);
		}
	}
}

void ADefaultAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ADefaultAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultAIController::OnTargetDetect(AActor* Target, 
	FAIStimulus const Stimulus)
{
	UE_LOG(Network, Warning, TEXT("Target Detect"));
	
	if (Stimulus.WasSuccessfullySensed())
	{
		AController* Controller = Cast<AController>(Target);

		if (IsValid(Controller))
			Target = Controller->GetPawn();

		if (Target != Blackboard->GetValueAsObject(TEXT("Target")))
		{
			Blackboard->SetValueAsObject(TEXT("Target"), Target);
		}
	}

	else
	{
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
	}
}
