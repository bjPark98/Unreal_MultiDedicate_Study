#include "ChatThread.h"
#include "../Network/PacketQueue.h"
#include "../Network/NetworkManager.h"
#include "../Network/NetSession.h"

CChatThread::CChatThread()
{
}

CChatThread::~CChatThread()
{
}

bool CChatThread::Init()
{
	CThreadBase::Init();

	CNetworkManager::GetInst()->CreatePacketQueue(TEXT("ChatPacketQueue"));

	mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("ChatPacketQueue"));

	return true;
}

void CChatThread::Stop()
{
	CThreadBase::Stop();
}

void CChatThread::Exit()
{
	CThreadBase::Exit();
}

uint32 CChatThread::ThreadRun()
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
