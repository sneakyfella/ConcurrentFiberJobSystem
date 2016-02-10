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
#include "JobScheduler.h"


TLS_VARIABLE(ThreadLocalStorage, ThreadArgPack);

JobScheduler::JobScheduler()
: mConsume(true)
, mFiberPool(100)
{
	InitializeCriticalSection(&mCS);
	//mFiberPool.Initialise();
}

JobScheduler::~JobScheduler()
{
	
	DeleteCriticalSection(&mCS);
}

void JobScheduler::Initialise(void)
{
	mFiberPool.Initialise();
}

void JobScheduler::Shutdown(void)
{
}

JobCounter JobScheduler::AddJob(Job job)
{
	JobCounter atomCounter(new AtomicCounter());
	atomCounter->store(1);

	JobBundle jb(job, atomCounter);

	mJobQueue.push(jb);

	return atomCounter;
}

JobCounter JobScheduler::AddJob(Uint32 numOfJobs, Job * job)
{
	JobCounter atomCounter(new AtomicCounter());
	atomCounter->store(numOfJobs);

	for (Uint32 i = 0; i < numOfJobs; ++i)
	{
		JobBundle jb = { job[i], atomCounter };
		mJobQueue.push(jb);
	}

	return atomCounter;
}

void JobScheduler::AddWaitingJob(WaitingJob waitjob)
{
	mWaitJobLock.lock();
	mWaitingJobs.push_back(waitjob);
	mWaitJobLock.unlock();
}

void JobScheduler::MainThreadInit(void * args)
{
}


THREAD_RET_SIGNATURE JobScheduler::ThreadStart(void * args)
{
	void * ptr = nullptr;
	ptr = ConvertThreadToFiberEx(nullptr, FIBER_FLAG_FLOAT_SWITCH);
	
	if (!ptr)
	{
		Stdout << "Error converting thread to fiber" << Stdendl;
		return 1;
	}

	SetTLSVariable(ThreadArgPack.Scheduler, JobScheduler::InstancePtr());
	SetTLSVariable(ThreadArgPack.OwningThread, (Thread*)args);
	SetTLSVariable(ThreadArgPack.CurrentFiber, GetCurrentFiber());

	SetTLSVariable(ThreadArgPack.CountWaitFiber, ThreadArgPack.OwningThread->GetCounterFiber()->CBLFiberHandle());
	SetTLSVariable(ThreadArgPack.SwitchFiber, ThreadArgPack.OwningThread->GetSwitchFiber()->CBLFiberHandle());

	JobScheduler* referenceToThis = (JobScheduler*)args;
	return referenceToThis->ThreadMain(args);
}

DWORD JobScheduler::ThreadMain(void * args)
{
	FiberMain(args);

	return 0;
}


FIBER_START_FUNCTION_CLASS_IMPL(JobScheduler, FiberMain)
{
	while (ThreadArgPack.Scheduler->mConsume)
	{

		WaitingJob job;
		ThreadArgPack.Scheduler->mWaitJobLock.lock();
		// If there are waiting jobs
	    // Looking for completed jobs
		bool waitingTaskReady = false;
		std::vector<WaitingJob>::iterator it = std::find_if(ThreadArgPack.Scheduler->mWaitingJobs.begin(),
															ThreadArgPack.Scheduler->mWaitingJobs.end(),
															[&waitingTaskReady] (const WaitingJob& job)->bool 
															{ 
																if (job.Counter->load() == job.Value)
																{
																	waitingTaskReady = true;
																	return true;
																}

																return false;
															} );
		//std::vector<WaitingJob>::iterator it = ThreadArgPack.Scheduler->mWaitingJobs.begin();

		// wait job completed and has been found
		if (it != ThreadArgPack.Scheduler->mWaitingJobs.end())
		{
			job = (*it);
			// Last element, avoiding self assignment
			if ((*it) != ThreadArgPack.Scheduler->mWaitingJobs.back())
			{
				(*it) = std::move(ThreadArgPack.Scheduler->mWaitingJobs.back());
			}
			ThreadArgPack.Scheduler->mWaitingJobs.pop_back();
		}
		ThreadArgPack.Scheduler->mWaitJobLock.unlock();

		if (waitingTaskReady) {
			ThreadArgPack.Scheduler->SwitchFiber(job.Owner);
		}

		// No wait jobs are available, GET TO WORK on the next job
		{
			JobBundle nextJob;
			if (ThreadArgPack.Scheduler->mJobQueue.try_pop(nextJob))
			{
				nextJob.Job.ExecuteJob();
				nextJob.JobCounter->fetch_sub(1);
			}
		}
	}
}
void JobScheduler::SwitchFiber(FiberHandle destFiber)
{
	FiberHandle curr = GetCurrentFiber();

	SetTLSVariable(ThreadArgPack.CurrentFiber, curr);
	SetTLSVariable(ThreadArgPack.NextFiber, destFiber);

	Fiber::CBLSwitchToFiber(destFiber);
}

FIBER_START_FUNCTION_CLASS_IMPL(JobScheduler, FiberSwitch)
{
	while (true)
	{
		// Push the fiber i came from to free pool
		//ThreadArgPack.OwningThread->FiberPool.PushFreeFiber(GetTLSVariable(ThreadArgPack.CurrentFiber));
		ThreadArgPack.Scheduler->mFiberPool.PushFreeFiber(ThreadArgPack.CurrentFiber);

		// Switch to desired fiber
		// reason for this is because when adding myself to the queue,
		// another thread can pop it off and execute before this fiber can execute it.
		// hence it will crash
		Fiber::CBLSwitchToFiber(ThreadArgPack.NextFiber);
	}
}
void JobScheduler::WaitForCounter(JobCounter & counter, Uint32 val)
{
	// Job has completed, hence load == 0, return from function
	if (counter->load() == 0)
		return;

	// Job has not completed, hence load != 0, switch to another fiber

	FiberHandle curr = GetCurrentFiber();
	FiberHandle next = mFiberPool.PopFreeFiber();
	SetTLSVariable(ThreadArgPack.CurrentFiber, curr);
	SetTLSVariable(ThreadArgPack.NextFiber, next);
	SetTLSVariable(ThreadArgPack.JobValue, val);
	SetTLSVariable(ThreadArgPack.JobCounter, counter.get());

	ASSERT(next, "Ran out of fibers");
	Fiber::CBLSwitchToFiber(ThreadArgPack.CountWaitFiber);

}
FIBER_START_FUNCTION_CLASS_IMPL(JobScheduler, FiberCounter)
{
	while (true)
	{
		WaitingJob waitJob(ThreadArgPack.CurrentFiber, // the jobbed fiber
						   ThreadArgPack.JobCounter,   // The counter this fiber is waiting for
						   ThreadArgPack.JobValue);    // value to countdown

		ThreadArgPack.Scheduler->AddWaitingJob(waitJob);
		
		Fiber::CBLSwitchToFiber(ThreadArgPack.NextFiber);

	}
}