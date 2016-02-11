// Precompiled Headers //
#include "stdAfx.h"
#include "../Thread/ForwardDeclarations.h"
#include "../Thread/FunctionLogger.h"
#include <gtest/gtest.h>

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
}

TEST(FunctionLogging, FunctionLoggingTest)
{

    DECLARE_JOBS(TestJob4, nullptr, 5);
    JobCounter temp = ADD_JOB_ARRAY(TestJob4, 5);

    while (FunctionLogger::Instance().GetFunctionLogSize("TestJob4") != 5)
    {
    }

    FunctionLogger::Instance().Write(0, 0);
    FunctionLogger::Instance().ClearFunctionLog();
}