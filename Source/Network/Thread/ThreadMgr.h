// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ThreadBase.h"

struct FThreadInfo
{
	FRunnableThread* Thread;
	CThreadBase* Worker;
};

class NETWORK_API CThreadMgr
{
private:
	CThreadMgr();
	~CThreadMgr();

private:
	TMap<FString, FThreadInfo*>	mThreadMap;

public:
	bool Init();
	bool SuspendThread(const FString& Name, bool Pause);
	bool RemoveThread(const FString& Name);

public:
	template <typename T>
	FThreadInfo* CreateThread(const FString& Name)
	{
		// map에 같은 이름이 있을 경우 빠져나간다.
		if (mThreadMap.Contains(Name))
			return nullptr;

		FThreadInfo* Info = new FThreadInfo;

		Info->Worker = new T;
		Info->Worker->SetName(Name);

		// 실제 스레드를 생성하고 스레드가 동작시켜줄 FRunnable 클래스로
		// 생성된 객체를 넘겨준다.
		Info->Thread = FRunnableThread::Create(Info->Worker, *Name);

		mThreadMap.Emplace(Name, Info);

		return Info;
	}



private:
	static CThreadMgr* mInst;

public:
	static CThreadMgr* GetInst()
	{
		if (!mInst)
			mInst = new CThreadMgr;

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
