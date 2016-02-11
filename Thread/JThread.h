/* This source file is part of the concurrent Fiber based Framework.
*
* Copyright (c) 2015-2016 Joshua Chew
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
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
    //! Getter to the thread's personal switching fiber
    //! @return Fiber *  ptr to fiber
	Fiber * GetSwitchFiber(void) const;
    //! Getter to the thread's personal counter waiting fiber
    //! @return Fiber *  ptr to fiber
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