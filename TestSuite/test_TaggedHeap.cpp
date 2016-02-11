// Precompiled Headers //
#include "stdAfx.h"
#include "../Thread/ForwardDeclarations.h"
#include <gtest/gtest.h>

struct TestStruct
{
    Uint32 x;
    Uint32 y;
};

inline bool operator==(const TestStruct & lhs, const TestStruct & rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

void MoveTestShit(void*args)
{
    PROFILER_BEGIN();
    TestStruct * test = reinterpret_cast<TestStruct*>(args);

    for (int i = 0; i < 100; ++i)
    {
        test->x++;
        test->y++;
    }
    PROFILER_END();
}

void AllocatorTest(void*args)
{
    LinearAllocator linearAlloc(KILOBYTES(2), TaggedHeap::Instance().GetMemoryBlock("Gameplay"));
    //;

    TestStruct * te[20]; //= (TestShit*)linearAlloc.Allocate(sizeof(TestShit));

    Job jArray[20];

    for (int i = 0; i < 20; ++i)
    {
        te[i] = (TestStruct*)linearAlloc.Allocate(sizeof(TestStruct));
        jArray[i].InitialiseJob(MoveTestShit, te[i], 0, "testing");
    }

    JobCounter counter = JobScheduler::Instance().AddJob(20, jArray);

    JobScheduler::Instance().WaitForCounter(counter, 20);

    TestStruct finalResult = { 100, 100 };

    for (int i = 0; i < 20; ++i)
    {
        ASSERT_EQ(finalResult, *te[i]);
    }

    linearAlloc.Free();
}
TEST(TaggedHeap, TaggedHeapTest)
{
    DECLARE_JOB(AllocatorTest, nullptr);
    ADD_JOB(AllocatorTest);
}