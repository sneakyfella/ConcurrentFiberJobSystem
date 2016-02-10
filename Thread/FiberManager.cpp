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

#if CONSOLE_PRINT_MODE
		Stdout  << "FiberID : " << ptr->GetFiberID() << Stdendl;
#endif

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
