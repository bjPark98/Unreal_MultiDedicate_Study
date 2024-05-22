// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadBase.h"

CThreadBase::CThreadBase()
{
}

CThreadBase::~CThreadBase()
{
}

bool CThreadBase::Init()
{
	// 시작용 이벤트 생성
	mStartEvent = FPlatformProcess::GetSynchEventFromPool(true);

	return true;
}

uint32 CThreadBase::Run()
{
	mStartEvent->Wait();

	FPlatformProcess::ReturnSynchEventToPool(mStartEvent);

	do
	{
		if (ThreadRun() == 0)
			break;
	} while (mLoop);

	return 0;
}

void CThreadBase::Stop()
{
}

void CThreadBase::Exit()
{
	mLoop = false;
}
