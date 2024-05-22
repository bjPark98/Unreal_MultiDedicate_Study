// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "DefaultAIController.h"
#include "AIState.h"
#include "AISpawnPoint.h"
#include "AIAnimInstance.h"
#include "../UI/AIHUDWidget.h"

// Sets default values
AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mHPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));

	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	mMovement->SetUpdatedComponent(mCapsule);

	mHPWidget->SetupAttachment(mMesh);

	mCapsule->SetCollisionProfileName(TEXT("AI"));

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mHPWidget->SetRelativeLocation(FVector(0.0, 0.0, 200.0));
	mHPWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget>	HPWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_AIHP.UI_AIHP_C'"));

	if (HPWidgetClass.Succeeded())
		mHPWidget->SetWidgetClass(HPWidgetClass.Class);

	mHPWidget->SetDrawSize(FVector2D(200.0, 50.0));

	// 루트컴포넌트로 캡슐을 지정한다.
	SetRootComponent(mCapsule);

	mMovement->MaxSpeed = 300.f;

	// Mesh를 Capsule의 Child로 지정한다.
	mMesh->SetupAttachment(mCapsule);

	AIControllerClass = ADefaultAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SetReplicates(true);

	SetCanBeDamaged(true);
}

void AAIPawn::ChangeAnimType_Implementation(uint8 AnimType)
{
	mAnimInst->ChangeAnim(AnimType);
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	mAnimInst = Cast<UAIAnimInstance>(mMesh->GetAnimInstance());

	mHPBar = Cast<UAIHUDWidget>(mHPWidget->GetWidget());

	mHPBar->AddConstructDelegate<AAIPawn>(this, &AAIPawn::HPCallback);
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 이 AIPawn을 생성해준 SpawnPoint가 있을 경우
	// 해당 SpawnPoint의 생성된 오브젝트 정보를 초기화한다.
	if (mSpawnPoint)
	{
		mSpawnPoint->ClearSpawnObject();
	}
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, 
	AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent,
		EventInstigator, DamageCauser);

	UE_LOG(Network, Warning, TEXT("Damage : %.5f"), DamageAmount);

	DamageAmount = DamageAmount - mState->GetDefense();
	DamageAmount = DamageAmount < 1.f ? 1.f : DamageAmount;

	mState->AddHP(-DamageAmount);

	AddUIHP(mState->GetHP() / (float)mState->GetHPMax());

	//mHPBar->SetAIHP(mState->GetHP() / (float)mState->GetHPMax());

	// 플레이어 컨트롤러로부터 MainWidget을 얻어와서 체력을 감소시킨다.

	return DamageAmount;
}

void AAIPawn::HPCallback()
{
	mHPBar->SetAIName(mState->GetAIName());
	mHPBar->SetAIHP(mState->GetHP() / (float)mState->GetHPMax());
}

void AAIPawn::AddUIHP_Implementation(float HPPercent)
{
	if (!HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Client Call"));
		mHPBar->SetAIHP(HPPercent);
	}

	else
	{
		UE_LOG(Network, Warning, TEXT("Server Call"));
	}
}

