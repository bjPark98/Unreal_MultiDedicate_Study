// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetworkGameMode.h"
#include "NetworkCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "NetworkPlayerController.h"

ANetworkGameMode::ANetworkGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_PlayerController.BP_PlayerController_C'"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ANetworkGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(Network, Warning, TEXT("GameMode BeginPlay"));
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("GameMode"));
}

APlayerController* ANetworkGameMode::Login(UPlayer* NewPlayer, 
	ENetRole InRemoteRole, const FString& Portal, const FString& Options, 
	const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal, 
		Options, UniqueId, ErrorMessage);

	//FString	InputName;

	//// 리턴이 true일 경우 값을 얻어왔다는 의미이다.
	//if (FParse::Value(*Options, TEXT("InputName="), InputName))
	//{
	//	UE_LOG(Network, Warning, TEXT("Name : %s"), *InputName);
	//}

	return result;
}

void ANetworkGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	/*ANetworkPlayerController* PC = Cast<ANetworkPlayerController>(NewPlayer);

	PC->SetTeamNumber(mTeamNumber);

	++mTeamNumber;*/
}
