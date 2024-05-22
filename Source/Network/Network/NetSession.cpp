// Fill out your copyright notice in the Description page of Project Settings.


#include "NetSession.h"

CNetSession::CNetSession()
{
}

CNetSession::~CNetSession()
{
	Close();
}

bool CNetSession::Connect(const FString& IPAddr, int32 Port)
{
	// 소켓을 생성한다.
	mSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(
		NAME_Stream, TEXT("Default"), false);

	// IP주소와 포트번호를 만들어준다.
	FIPv4Address	IPObject;

	// 문자열로 들어온 주소를 정수로 만들어준다.
	FIPv4Address::Parse(IPAddr, IPObject);

	TSharedRef<FInternetAddr>	Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	Addr->SetIp(IPObject.Value);
	Addr->SetPort(Port);

	mConnect = mSocket->Connect(*Addr);

	return mConnect;
}

void CNetSession::Close()
{
	if (mConnect)
	{
		mSocket->Close();
		delete mSocket;

		mSocket = nullptr;
		mConnect = false;
	}
}

bool CNetSession::Receive(int32& PacketHeader, int32& Length,
	uint8* Packet)
{
	if (!mConnect)
		return false;

	bool Result = mSocket->Recv(mRecvBuffer, 1024, Length);

	if (!Result || Length == 0)
		return false;

	FMemory::Memcpy(&PacketHeader, mRecvBuffer, 4);
	FMemory::Memcpy(&Length, mRecvBuffer + 4, 4);
	FMemory::Memcpy(Packet, mRecvBuffer + 8, Length);

	return true;
}

bool CNetSession::Send(int32 PacketHeader, int32 Length, uint8* Packet)
{
	if (!mConnect)
		return false;

	FMemory::Memcpy(mSendBuffer, &PacketHeader, 4);
	FMemory::Memcpy(mSendBuffer + 4, &Length, 4);
	FMemory::Memcpy(mSendBuffer + 8, Packet, Length);

	return mSocket->Send(mSendBuffer, Length + 8, Length);
}
