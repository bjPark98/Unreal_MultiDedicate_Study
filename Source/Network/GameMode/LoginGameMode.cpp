// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "../Player/Login/LoginPlayerController.h"
#include "../Network/NetworkManager.h"
#include "../Thread/ThreadMgr.h"
#include "../Thread/RecvThread.h"
#include "../Network/NetSession.h"
#include "../Network/PacketQueue.h"

ALoginGameMode::ALoginGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = ALoginPlayerController::StaticClass();
	
	DefaultPawnClass = nullptr;
}

void ALoginGameMode::InitGame(const FString& MapName, 
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// 채팅서버에 커넥트 요청을 한다.
	CNetworkManager::GetInst()->Connect(TEXT("LoginSession"),
		TEXT("127.0.0.1"), 10005);

	CNetSession* Session = CNetworkManager::GetInst()->FindSession(TEXT("LoginSession"));

	FThreadInfo* ThreadInfo = CThreadMgr::GetInst()->CreateThread<CRecvThread>(TEXT("LoginThread"));

	ThreadInfo->Worker->SetLoop(true);
	((CRecvThread*)ThreadInfo->Worker)->SetSession(Session);

	// 스레드를 동작시켜준다.
	ThreadInfo->Worker->Start();
	//CThreadMgr::GetInst()->SuspendThread(TEXT("LoginThread"), false);

	mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("LoginPacketQueue"));
}

void ALoginGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mQueue->Empty())
	{
		int32	Header = 0, Length = 0;
		uint8	Packet[1024] = {};

		mQueue->Pop(Header, Length, Packet);

		switch (Header)
		{
		case LPH_Login:
			bool	LoginEnable;

			FMemory::Memcpy(&LoginEnable, Packet, 1);

			if (LoginEnable)
			{
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("127.0.0.1:10000"));
				UE_LOG(Network, Warning, TEXT("Login"));
			}

			else
			{
				UE_LOG(Network, Warning, TEXT("Login Failed"));
			}
			break;
		}
	}
}
