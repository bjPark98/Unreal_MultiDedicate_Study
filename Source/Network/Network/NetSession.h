// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

class NETWORK_API CNetSession
{
public:
	CNetSession();
	~CNetSession();

private:
	FString		mName;
	FSocket* mSocket = nullptr;
	bool	mConnect = false;
	uint8	mRecvBuffer[1024] = {};
	uint8	mSendBuffer[1024] = {};

public:
	void SetName(const FString& Name)
	{
		mName = Name;
	}

	const FString& GetName()	const
	{
		return mName;
	}

	bool IsConnect()	const
	{
		return mConnect;
	}

public:
	bool Connect(const FString& IPAddr, int32 Port);
	void Close();
	bool Receive(int32& PacketHeader, int32& Length, uint8* Packet);
	bool Send(int32 PacketHeader, int32 Length, uint8* Packet);
};
