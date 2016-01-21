#pragma once


#include "ForwardDeclarations.h"
#include "ThreadTypeDefs.h"
#include "FiberManager.h"

class Thread
{
public:
	
	Thread();
	~Thread();

	void Initialise(void);

	void Shutdown(void);

	ThreadID GetThreadID(void) const;

	Fiber * GetSwitchFiber(void) const;
	Fiber * GetCounterFiber(void) const;

private:

	void CBLCreateThread(ThreadStartRoutine startRout, void * args, Uint32 stackSize);

	void CBLCloseHandle(void);

	void CBLExitThread(void);

	bool CBLSuspendThread(void);

	bool CBLResumeThread(void);

	
private:

	Uint32       mCoreAffinity;
	Uint32       mStackSize;
	ThreadID     mThreadID;
	ThreadHandle mThreadHandle;
	
	Fiber*   mSwitchFiber;
	Fiber*   mCounterFiber;
	//Uint32
	//TLS_VARIABLE(Int32, test);

	friend class ThreadManager; // Only ThreadManager should be creating or destroying threads.
};

template <typename T>
inline void SetTLSVariable(T & dest, T source)
{
	dest = source;
}
template <typename T>
inline T GetTLSVariable(const T & dest)
{
	return dest;
}