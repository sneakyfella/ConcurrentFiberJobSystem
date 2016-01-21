#include "stdafx.h"
#include "JThread.h"

const Uint32 Default_Stack_Size = 1048576;

Thread::Thread()
: mCoreAffinity(-1)
, mStackSize(0)
, mThreadID(0)
, mThreadHandle(nullptr)
{
}

Thread::~Thread()
{
	delete mSwitchFiber;
	delete mCounterFiber;
}

void Thread::Initialise(void)
{
	// Create a fiber pool within the thread.
	//FiberPool.Initialise();
	//FiberPool.SetOwningThread(this);
}

void Thread::Shutdown(void)
{
	//FiberPool.Shutdown();
	mSwitchFiber->Shutdown();
	mCounterFiber->Shutdown();
	CBLCloseHandle();
	CBLExitThread();
	
}
ThreadID Thread::GetThreadID(void) const
{
	return mThreadID;
}
Fiber* Thread::GetSwitchFiber(void) const
{
	return mSwitchFiber;
}
Fiber* Thread::GetCounterFiber(void) const
{
	return mCounterFiber;
}
void Thread::CBLCreateThread(ThreadStartRoutine startRout, void * args, Uint32 stackSize)
{
	mThreadHandle = CreateThread(nullptr, stackSize, startRout, args, CREATE_SUSPENDED, &mThreadID);
	
	if (!mThreadHandle)
	{
		Stdout << "Thread creation unsuccessful" << Stdendl;
	}
	else
	{
		Stdout << "Thread created successfully" << Stdendl;
		Stdout << "Thread ID : " << mThreadID << Stdendl;
	}

	Initialise();
	mSwitchFiber = new Fiber();
	mSwitchFiber->CBLCreateFiber(JobScheduler::FiberSwitch, 0, this, 0);
	mCounterFiber = new Fiber();
	mCounterFiber->CBLCreateFiber(JobScheduler::FiberCounter, 0, this, 1);
}

void Thread::CBLCloseHandle(void)
{
	CloseHandle(mThreadHandle);
}

void Thread::CBLExitThread(void)
{
	if (mThreadHandle)
		ExitThread(0);
}

bool Thread::CBLSuspendThread(void)
{
	if (mThreadHandle)
	{
		// anything else other than -1 is success
		return SuspendThread(mThreadHandle) != -1;
	}

	return false;
}

bool Thread::CBLResumeThread(void)
{
	if (mThreadHandle)
	{
		// anything else other than -1 is success
		return ResumeThread(mThreadHandle) != -1;
	}
	return false;
}

