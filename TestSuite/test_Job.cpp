// Precompiled Headers //
#include "stdAfx.h"
#include "../Thread/ForwardDeclarations.h"
#include <gtest/gtest.h>

void TestJob(void * args)
{
    int a = 0;
    for (int i = 0; i < 100; ++i)
    {
        ++a;
    }

    a += 20;
    ASSERT_EQ(a, 120);
}
void TestJob2(void * args)
{
    int a = 0;

    for (int i = 0; i < 200; ++i)
    {
        ++a;
    }
    a += 20;
    ASSERT_EQ(a, 220);
}
void TestJob3(void * args)
{
    int a = 0;

    for (int i = 0; i < 800; ++i)
    {
        ++a;
    }

    a += 20;

    ASSERT_EQ(a, 820);
}
TEST(Job, JobTest)
{
    DECLARE_JOBS(TestJob, nullptr, 5);
    JobCounter tJob1 = ADD_JOB_ARRAY(TestJob, 5);

    DECLARE_JOBS(TestJob2, nullptr, 5);
    JobCounter tJob2 = ADD_JOB_ARRAY(TestJob2, 5);

    DECLARE_JOBS(TestJob3, nullptr, 5);
    JobCounter tJob3 = ADD_JOB_ARRAY(TestJob3, 5);
}