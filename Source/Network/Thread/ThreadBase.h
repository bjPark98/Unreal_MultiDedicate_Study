// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

class NETWORK_API CThreadBase	:
	public FRunnable
{
	friend class CThreadMgr;

protected:
	CThreadBase();
	~CThreadBase();

protected:
	bool	mLoop = false;
	FString	mName;
	FEvent*	mStartEvent;

public:
	void SetName(const FString& Name)
	{
		mName = Name;
	}

	void SetLoop(bool Loop)
	{
		mLoop = Loop;
	}

	void Start()
	{
		mStartEvent->Trigger();
	}

public:
	virtual bool Init();
	virtual uint32 Run() final;
	virtual void Stop();
	virtual void Exit();

protected:
	virtual uint32 ThreadRun() = 0;
};
