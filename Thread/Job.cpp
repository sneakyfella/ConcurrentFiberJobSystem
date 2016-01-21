#include "stdafx.h"
#include "Job.h"


Job::Job()
: mFunction(nullptr)
{
}

Job::~Job()
{
}

void Job::InitialiseJob(JobFunction func, void * args, Uint32 id,  const char *name, ThreadPriority prio)
{
	mFunction = func;
	mJobArgs = args;
	mID = id;
	mPriority = prio;
	//strcpy(mName, name);
	mName = name;
}

void Job::ExecuteJob(void)
{
	if (mFunction)
	{
#if CONSOLE_PRINT_MODE
		Stdout << mName << Stdendl;
#endif
		//PROFILER_BEGIN_W_NAME(mName.c_str());
		mFunction(mJobArgs);
		//PROFILER_END_W_NAME(mName.c_str());
	}
}

Uint32 Job::GetJobID(void) const
{
	return mID;
}

ThreadPriority Job::GetJobPriority(void) const
{
	return mPriority;
}
