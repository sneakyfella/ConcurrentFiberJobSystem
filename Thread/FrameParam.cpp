#include "stdafx.h"
#include "FrameParam.h"
FrameParam::FrameParam(void)
    :mAllocator(KILOBYTES(2), TaggedHeap::Instance().GetMemoryBlock("Cool"))
    ,mFrameNumber(0)
{
}

FrameParam::~FrameParam(void)
{
    mAllocator.Free();
}
