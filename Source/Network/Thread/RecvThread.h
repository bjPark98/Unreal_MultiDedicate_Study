// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ThreadBase.h"

class NETWORK_API CRecvThread	:
	public CThreadBase
{
	friend class CThreadMgr;

private:
	CRecvThread();
	~CRecvThread();

private:
	class CNetSession* mSession = nullptr;
	class CPacketQueue* mQueue = nullptr;

public:
	void SetSession(class CNetSession* Session)
	{
		mSession = Session;
	}

public:
	virtual bool Init();
	virtual void Stop();
	virtual void Exit();

protected:
	virtual uint32 ThreadRun();
};
