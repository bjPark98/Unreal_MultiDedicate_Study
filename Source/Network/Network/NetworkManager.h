// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "NetworkINfo.h"


class NETWORK_API CNetworkManager
{
private:
	CNetworkManager();
	~CNetworkManager();

private:
	TMap<FString, class CNetSession*>	mSessionMap;
	TMap<FString, class CPacketQueue*>	mQueueMap;

public:
	bool Init();
	bool CheckSession(const FString& Name);
	bool Connect(const FString& Name, const FString& IPAddr, int32 Port);
	bool Close(const FString& Name);
	class CNetSession* FindSession(const FString& Name);
	bool RemoveSession(const FString& Name);
	bool Send(const FString& Name, int32 PacketHeader, int32 Length, uint8* Packet);

	bool CreatePacketQueue(const FString& Name);
	class CPacketQueue* FindPacketQueue(const FString& Name);

private:
	static CNetworkManager* mInst;

public:
	static CNetworkManager* GetInst()
	{
		if (!mInst)
			mInst = new CNetworkManager;

		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};
