// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketQueue.h"

CPacketQueue::CPacketQueue()
{
}

CPacketQueue::~CPacketQueue()
{
}

void CPacketQueue::Push(int32 Header, int32 Length, uint8* Packet)
{
	FScopeLock	lock(&mCrt);

	if (mSize == 500)
		return;

	mTail = (mTail + 1) % 501;

	mQueue[mTail].Header = Header;
	mQueue[mTail].Length = Length;
	FMemory::Memcpy(mQueue[mTail].Packet, Packet, Length);

	++mSize;
}

void CPacketQueue::Pop(int32& Header, int32& Length, uint8* Packet)
{
	FScopeLock	lock(&mCrt);

	if (mSize == 0)
		return;

	mHead = (mHead + 1) % 501;

	Header = mQueue[mHead].Header;
	Length = mQueue[mHead].Length;

	FMemory::Memcpy(Packet, mQueue[mHead].Packet, Length);

	--mSize;
}

bool CPacketQueue::Empty()
{
	return mSize == 0;
}

int32 CPacketQueue::Size()
{
	return mSize;
}

void CPacketQueue::Clear()
{
	mTail = 0;
	mHead = 0;
	mSize = 0;
}
