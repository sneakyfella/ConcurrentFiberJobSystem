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
#include "FiberManager.h"
#include "Job.h"
#include "Singleton.h"
#include "ThreadTypeDefs.h"
#include "ConcurrentQueue.h"
#include <concurrent_vector.h>

#include <atomic>
#include <mutex>
#include <queue>

using namespace concurrency;
class JobScheduler : Noncopyable
{
public:
	JobScheduler();
	~JobScheduler();

	void Initialise(void);

	void Shutdown(void);

	JobCounter  AddJob(Job job);

	JobCounter  AddJob(Uint32 numOfJobs, Job * job);

	void AddWaitingJob(WaitingJob waitjob);

	static void MainThreadInit(void*args);

	static THREAD_RET_SIGNATURE ThreadStart(void * args);

	DWORD ThreadMain(void * args);


	static FIBER_START_FUNCTION(FiberMain);

	void SwitchFiber(FiberHandle destFiber);

	static FIBER_START_FUNCTION(FiberSwitch);

	void WaitForCounter(JobCounter & counter, Uint32 val);

	static FIBER_START_FUNCTION(FiberCounter);

	void Sort(void)
	{
	}
	FiberManager                       mFiberPool;
	concurrent_queue<JobBundle>              mJobQueue;
	std::vector<WaitingJob>            mWaitingJobs;
	std::mutex						   mWaitJobLock;
private:

	CRITICAL_SECTION mCS;

	bool mConsume;

	DECLARE_SINGLETON(JobScheduler);
};

#define ADD_JOB(func)\
JobScheduler::Instance().AddJob(func##job);
#define ADD_JOB_ARRAY(func, count)\
JobScheduler::Instance().AddJob(count,func##job);
#define WAIT_FOR_COUNTER(counter, val)\
JobScheduler::Instance().WaitForCounter(counter, val);