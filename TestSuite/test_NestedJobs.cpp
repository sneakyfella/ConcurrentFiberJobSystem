// Precompiled Headers //
#include "stdAfx.h"
#include "../Thread/ForwardDeclarations.h"
#include <gtest/gtest.h>

void TestJob5(void * args)
{
    PROFILER_BEGIN();
    int a = 0;
    for (int i = 0; i < 1800; ++i)
    {
        a = i + 1;
    }

    a += 20;
    PROFILER_END();
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

    DECLARE_JOBS(TestJob5, nullptr, 10);
    JobCounter temp = ADD_JOB_ARRAY(TestJob5, 10);
    WAIT_FOR_COUNTER(temp, 10);



    PROFILER_END();


}
TEST(NestedJobs, NestedJobTest)
{
    DECLARE_JOBS(NestedJob, nullptr, 5);
    JobCounter temp = ADD_JOB_ARRAY(NestedJob, 5);

    while (FunctionLogger::Instance().GetFunctionLogSize("TestJob5") != 50)
    {
    }

    FunctionLogger::Instance().Write(0, 0);
    FunctionLogger::Instance().ClearFunctionLog();
}