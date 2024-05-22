// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "NetworkInfo.h"


class NETWORK_API CPacketQueue
{
public:
	CPacketQueue();
	~CPacketQueue();

private:
	FPacketInfo	mQueue[501];
	int32		mHead = 0;
	int32		mTail = 0;
	int32		mSize = 0;
	FCriticalSection	mCrt;

public:
	void Push(int32 Header, int32 Length, uint8* Packet);
	void Pop(int32& Header, int32& Length, uint8* Packet);
	bool Empty();
	int32 Size();
	void Clear();
};
