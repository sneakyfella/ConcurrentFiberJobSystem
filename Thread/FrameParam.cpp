#include "stdafx.h"
#include "FrameParam.h"
FrameParam::FrameParam(Uint64 frameNumber)
    :mAllocator(KILOBYTES(2), TaggedHeap::Instance().GetMemoryBlock("Cool"))
    ,mFrameNumber(frameNumber)
{
}

FrameParam::~FrameParam(void)
{
    mAllocator.Free();
}
