#include "stdafx.h"
#include "ThreadManager.h"

ThreadManager::ThreadManager(void)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	mPhysicalCoreCount = sysInfo.dwNumberOfProcessors - 2;

	mPhysicalCoreCount = 6;
}

ThreadManager::~ThreadManager(void)
{
	Shutdown();
}

void ThreadManager::Initialise(void)
{
	CreateThreadPool();
}

void ThreadManager::Shutdown(void)
{
	FreeThreadPool();
}

void ThreadManager::CreateThreadPool(void)
{
	for (Uint32 i = 0; i < mPhysicalCoreCount; ++i)
	{
		Thread * ptr = new Thread();

		ptr->CBLCreateThread(JobScheduler::InstancePtr()->ThreadStart, ptr, 0);

		// Setting physical core affinity
		DWORD_PTR mask = 1ull << i;
		DWORD_PTR res = SetThreadAffinityMask(ptr->mThreadHandle, mask);

		mThreadPool.emplace(ptr->mThreadID, ptr);
	}
}

void ThreadManager::RunThreads(void)
{
	for (auto& thd : mThreadPool)
	{
#if CONSOLE_DEBUG_PRINT
		if (thd.second->CBLResumeThread())
		{
			Stdout << "Resuming Thread Success" << thd.second->mThreadID << Stdendl;
		}
#else
        thd.second->CBLResumeThread();
#endif
	}
}

void ThreadManager::FreeThreadPool(void)
{
	for (auto& thd : mThreadPool)
	{
		thd.second->Shutdown();
		delete thd.second;
	}

	mThreadPool.clear();
}
