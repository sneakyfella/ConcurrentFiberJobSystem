// Precompiled Headers //
#include "stdAfx.h"
#include "../Thread/ForwardDeclarations.h"
#include <gtest/gtest.h>



void ArbitraryJob(void*args)
{
    int a = 0;

    for (int i = 0; i < 800; ++i)
    {
        ++a;
    }

    a += 20;
}

void WaitForCounterFunc(void*args)
{
    DECLARE_JOBS(ArbitraryJob, nullptr, 5);
    JobCounter temp = ADD_JOB_ARRAY(ArbitraryJob, 5);
    WAIT_FOR_COUNTER(temp, 5);

    ASSERT_EQ(temp->load(), 0);

}
TEST(WaitForCounter, WaitForCounterTest)
{
    DECLARE_JOB(WaitForCounterFunc, nullptr);
    ADD_JOB(WaitForCounterFunc);
}