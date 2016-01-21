#include "stdafx.h"
#include "FiberManager.h"

FiberManager::FiberManager(Uint32 fiberCount)
: mFiberCount(fiberCount)
{
}

FiberManager::~FiberManager()
{
	Shutdown();
}

void FiberManager::Initialise(void)
{
	CreateFiberPool();
}

void FiberManager::Shutdown(void)
{
	FreeFiberPool();
}
FiberHandle FiberManager::PopFreeFiber(void)
{
	FiberHandle ret = nullptr;
	mFiberQueue.try_pop(ret);
	return ret;
}
void FiberManager::PushFreeFiber(FiberHandle hnd)
{
	mFiberQueue.push(hnd);
}
void FiberManager::CreateFiberPool(void)
{
	for (Uint32 i = 0; i < mFiberCount; ++i)
	{
		Fiber * ptr = new Fiber();

		FiberHandle fHnd = ptr->CBLCreateFiber(JobScheduler::InstancePtr()->FiberMain, 0, JobScheduler::InstancePtr(), i);
		mFiberQueue.push(fHnd);
		mFiberPool.emplace(ptr->GetFiberID(), ptr);

		Stdout  << "FiberID : " << ptr->GetFiberID() << Stdendl;
	}
}

void FiberManager::FreeFiberPool(void)
{
	for (auto & fbr : mFiberPool)
	{
		fbr.second->Shutdown();
		delete fbr.second;
	}
	mFiberPool.clear();
	// No clear for queues, so empty it
	//FiberQueue empty;
	//std::swap(mFiberQueue, empty);
	mFiberQueue.clear();
	
}
