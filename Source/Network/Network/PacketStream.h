// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkInfo.h"
#include "../GameInfo.h"

class NETWORK_API CPacketStream
{
public:
	CPacketStream();
	~CPacketStream();

private:
	uint8* mBuffer = nullptr;
	int	mLength = 0;

public:
	void SetBuffer(uint8* Buffer)
	{
		mBuffer = Buffer;
	}

	int GetLength()	const
	{
		return mLength;
	}

public:
	template <typename T>
	void AddData(const T* Data, int Length)
	{
		if (!mBuffer)
			return;

		FMemory::Memcpy(mBuffer + mLength, Data, Length);
		mLength += Length;
	}

	template <typename T>
	void GetData(T* Data, int Length)
	{
		FMemory::Memcpy(Data, mBuffer + mLength, Length);
		mLength += Length;
	}
};
