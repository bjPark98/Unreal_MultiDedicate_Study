// Fill out your copyright notice in the Description page of Project Settings.


#include "AIState.h"

// Sets default values for this component's properties
UAIState::UAIState()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAIState::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 리플리케이트 되는 모든 변수들을 여기에 등록한다.
	// DOREPLIFETIME은 현재 클래스 타입, 변수이름을 작성한다.
	DOREPLIFETIME(UAIState, mHP);
}

