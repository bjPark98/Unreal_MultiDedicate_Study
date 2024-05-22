// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvThread.h"
#include "../Network/PacketQueue.h"
#include "../Network/NetworkManager.h"
#include "../Network/NetSession.h"

CRecvThread::CRecvThread()
{
}

CRecvThread::~CRecvThread()
{
}

bool CRecvThread::Init()
{
	CThreadBase::Init();

	CNetworkManager::GetInst()->CreatePacketQueue(TEXT("LoginPacketQueue"));

	mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("LoginPacketQueue"));
	
	return true;
}

void CRecvThread::Stop()
{
	CThreadBase::Stop();
}

void CRecvThread::Exit()
{
	CThreadBase::Exit();
}

uint32 CRecvThread::ThreadRun()
{
	if (mSession)
	{
		int32	Header = 0, Length = 0;
		uint8	Packet[1024] = {};

		if (!mSession->Receive(Header, Length, Packet))
			return 0;

		mQueue->Push(Header, Length, Packet);
	}

	return 1;
}
