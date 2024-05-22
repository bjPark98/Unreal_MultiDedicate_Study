// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "../NetworkGameMode.h"
#include "../NetworkGameState.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mBody);

	mBody->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	mBody->SetCollisionProfileName(TEXT("Item"));

	mMesh->SetupAttachment(mBody);

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mMesh->SetIsReplicated(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>	Asset(TEXT("/Script/Engine.StaticMesh'/Game/ThirdPerson/Blueprints/Cube.Cube'"));

	if (Asset.Succeeded())
		mMesh->SetStaticMesh(Asset.Object);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	mBody->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::ItemOverlap);
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::ItemOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult)
{
	ANetworkGameState* GameState = GetWorld()->GetGameState<ANetworkGameState>();

	GameState->PickUpItem();

	GameState->AddTeamItem(true);

	Destroy();

	// 이 함수의 리턴이 true일 경우 서버, false일 경우 클라이언트 이다.
	//if (HasAuthority())
	//{
	//	ANetworkGameMode* GameMode = GetWorld()->GetAuthGameMode<ANetworkGameMode>();

	//	if (IsValid(GameMode))
	//		GameMode->PickUpItem();

	//	Destroy();


	//	//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("ItemOverlap"));
	//	//UE_LOG(Network, Warning, TEXT("ItemOverlap"));
	//}
}

