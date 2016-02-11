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
#include <atomic>


enum class ThreadPriority
{
	PRIORITY_LOW,
	PRIORITY_MEDIUM,
	PRIORITY_HIGH,
	PRIORITY_INSTANT
};

typedef std::atomic_ulong              AtomicCounter;
typedef std::shared_ptr<AtomicCounter> JobCounter;

class Job
{
    /***** Public Methods *****/
public:
    //! Default constructor.
	Job();
    //! Default destructor.
	~Job();
    //! Only Manager should be creating fibers
    //! static function for fibers to switch to
    //! @param	func	 Function to be jobified
    //! @param	args	 Pointer to args used for the function (USUALLY USES HEAP ALLOCATED ARGS)
    //! @param	id	     Job ID
    //! @param	name	 Job Name
    //! @param	prio	 Priority for job (TODO : not implemented yet)
	void InitialiseJob(JobFunction func, void * args, Uint32 id, const char *name ,ThreadPriority prio = ThreadPriority::PRIORITY_MEDIUM);
    //! Runs the function with args
	void ExecuteJob(void);

	Uint32 GetJobID(void) const;
	ThreadPriority GetJobPriority(void) const;

	JobFunction mFunction;
	void      * mJobArgs;

    /***** Private Members *****/
private:
	String mName;
	Uint32 mID;
	ThreadPriority mPriority;
};

struct JobBundle
{
	JobBundle()
	{}
	JobBundle(Job j, JobCounter jc)
		: Job(j)
		, JobCounter(jc) {}
	typedef Job        JobClass;
	typedef JobCounter JobCounterClass;
	JobClass		Job;
	JobCounterClass JobCounter;
};

struct WaitingJob
{
	WaitingJob()
		: Owner(nullptr)
		, Counter(nullptr)
		, Value(0) {}
	WaitingJob(FiberHandle fiber, AtomicCounter * counter, Uint32 val)
		: Owner(fiber)
		, Counter(counter)
		, Value(val) {}

	bool operator==(const WaitingJob & rhs) const {
		return Owner == rhs.Owner;
	}

	bool operator!=(const WaitingJob & rhs) const {
		return Owner != rhs.Owner;
	}

	bool operator()(const WaitingJob & rhs) const{
		return Counter->load() == Value;
	}

	WaitingJob & operator=(const WaitingJob & rhs) {
		Owner   = rhs.Owner;
		Counter = rhs.Counter;
		Value   = rhs.Value;
		return *this;
	}

	FiberHandle		Owner;
	AtomicCounter * Counter;
	Uint32			Value;
};

#define DECLARE_JOB(func, args)\
Job func##job;\
func##job.InitialiseJob(func, args,0, #func);

#define DECLARE_JOB_W_PRIORITY(func, args, priority)\
Job func##job;\
func##job.InitialiseJob(func, args,0, #func, priority);

#define DECLARE_JOBS(func, args, count)\
Job func##job[count];\
for(int i = 0; i < count; ++i){\
func##job[i].InitialiseJob(func, args,i,#func);\
}
#define DECLARE_JOBS_W_PRIORITY(func, args, count, priority)\
Job func##job[count];\
for(int i = 0; i < count; ++i){\
func##job[i].InitialiseJob(func, args,i,#func,priority);\
}

//JobScheduler::Instance().AddJob(count, temp);