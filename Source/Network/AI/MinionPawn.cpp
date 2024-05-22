// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionPawn.h"
#include "AIState.h"

AMinionPawn::AMinionPawn()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Core_Dawn.Minion_Lane_Melee_Core_Dawn'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/ABP_Minion.ABP_Minion_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mCapsule->SetCapsuleHalfHeight(90.f);
	mCapsule->SetCapsuleRadius(30.f);

	mSwordL = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordL"));
	mSwordR = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordR"));

	mSwordL->SetCollisionProfileName(TEXT("MonsterAttack"));
	mSwordR->SetCollisionProfileName(TEXT("MonsterAttack"));

	mSwordL->SetupAttachment(mMesh, TEXT("Socket_Sword_L"));
	mSwordR->SetupAttachment(mMesh, TEXT("Socket_Sword_R"));

	mSwordL->SetBoxExtent(FVector(5.0, 58.0, 15.0));
	mSwordR->SetBoxExtent(FVector(5.0, 58.0, 15.0));

	mSwordL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mSwordR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMinionPawn::BeginPlay()
{
	Super::BeginPlay();

	mSwordL->OnComponentBeginOverlap.AddDynamic(this, &AMinionPawn::AttackOverlap);
	mSwordR->OnComponentBeginOverlap.AddDynamic(this, &AMinionPawn::AttackOverlap);

	//mSwordR->OnComponentHit
}

void AMinionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMinionPawn::EnableAttack(bool Enable, EAttackCollider Type)
{
	if (HasAuthority())
	{
		if (Enable)
		{
			switch (Type)
			{
			case EAttackCollider::Left:
				mSwordL->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				break;
			case EAttackCollider::Right:
				mSwordR->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				break;
			case EAttackCollider::Both:
				mSwordL->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				mSwordR->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				break;
			}
		}

		else
		{
			switch (Type)
			{
			case EAttackCollider::Left:
				mSwordL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				break;
			case EAttackCollider::Right:
				mSwordR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				break;
			case EAttackCollider::Both:
				mSwordL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				mSwordR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				break;
			}
		}
	}
}

void AMinionPawn::AttackOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		FDamageEvent	DmgEvent;

		OtherActor->TakeDamage(mState->GetAttack(), DmgEvent, GetController(),
			this);
	}
}
