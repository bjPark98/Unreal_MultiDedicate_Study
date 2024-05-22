#pragma once

#include "ThreadBase.h"

class NETWORK_API CChatThread :
	public CThreadBase
{
	friend class CThreadMgr;

private:
	CChatThread();
	~CChatThread();

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

