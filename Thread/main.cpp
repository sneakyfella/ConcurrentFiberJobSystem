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

struct TestShit
{
    Uint32 x;
    Uint32 y;
};
void MoveTestShit(void*args)
{
    PROFILER_BEGIN();
    TestShit * test = reinterpret_cast<TestShit*>(args);
    for (int i = 0; i < 200; ++i)
    {
        test->x = 20 + i;
        test->y = 30 + i;
    }

    PROFILER_END();
}
void TestJob(void * args)
{
	for (int i = 0; i < 100; ++i)
	{
		int a = i + 1;
	}
	//Stdout << "Job 1" << Stdendl;
}
void TestJob2(void * args)
{
	for (int i = 0; i < 200; ++i)
	{
		int a = i + 1;
	}
	//Stdout << "Job 2" << Stdendl;
}
void TestJob3(void * args)
{
	int a = 0;
	for (int i = 0; i < 800; ++i)
	{
		a = i + 1;
	}

	a += 20;
	//Stdout << "Job 3" << Stdendl;
}
void TestJob4(void * args)
{
	PROFILER_BEGIN();
	int a = 0;
	for (int i = 0; i < 1800; ++i)
	{
		a = i + 1;
	}

	a += 20;
	PROFILER_END();
	//Stdout << "Job 3" << Stdendl;
}
void NestedJob(void * args)
{
	PROFILER_BEGIN();
	int a = 0;
	for (int i = 0; i < 800; ++i)
	{
		a = i + 1;
	}

	a += 20;

	DECLARE_JOBS(TestJob4, nullptr,10);
	JobCounter temp = ADD_JOB_ARRAY(TestJob4, 10);
	WAIT_FOR_COUNTER(temp, 10);
	//Stdout << "Wait Complete" << Stdendl;
	PROFILER_END();
}
int main()
{
	//ASSERT(false, "hello");
	Stdout << "Main Thread init : " << GetCurrentThreadId() << Stdendl;
	ThreadManager tMnger;
	JobScheduler::Instance();
	tMnger.Initialise();
	//
	tMnger.RunThreads();
	//PROFILER_BEGIN();
    GET_SINGLETON(JobScheduler).Initialise();
	//JobScheduler::Instance().Initialise();
	//PROFILER_END();

	DECLARE_JOBS(NestedJob, nullptr, 5);
	JobCounter temp = ADD_JOB_ARRAY(NestedJob, 5);

	getchar();


    
    LinearAllocator linearAlloc(KILOBYTES(2), TaggedHeap::Instance().GetMemoryBlock("Gameplay"));
    //;
    
    TestShit * te[20]; //= (TestShit*)linearAlloc.Allocate(sizeof(TestShit));

    for (int i = 0; i < 20; ++i)
    {
        te[i] = (TestShit*)linearAlloc.Allocate(sizeof(TestShit));
        DECLARE_JOB(MoveTestShit, te[i]);
        ADD_JOB(MoveTestShit);
    }
    JobScheduler::Instance().Sort();
    FunctionLogger::Instance().Write(0, 0);

    getchar();
    //temp[0]
    //DECLARE_JOBS(MoveTestShit, nullptr, 5);
    while (1)
	//{
	//	std::cout << std::chrono::high_resolution_clock::now().
	//}
	//Stdout << "Main Thread Closing." << Stdendl;

	

	tMnger.Shutdown();
    return 0;
}

