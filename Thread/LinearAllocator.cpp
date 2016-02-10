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
#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t poolSize)
	: BaseAllocator(poolSize)
	, mCurrentPos(BaseAllocator::GetStart())
{
}

LinearAllocator::LinearAllocator(Uint32 poolSize, MemoryBlock * memPool)
    : BaseAllocator(poolSize, memPool)
    , mCurrentPos(BaseAllocator::GetStart())
{
    memPool->FlushMemoryBlock();
}

LinearAllocator::~LinearAllocator(void)
{
}

void * LinearAllocator::Allocate(Uint32 size, Uint8 alignment)
{
	ASSERT(size != 0, "Size = 0");

	Uint8 memAlign = AlignForwardAdjustment(mCurrentPos, alignment);

	Uint32 memUsed = size + memAlign;

	if(BaseAllocator::CheckAllocatorOverflow(memUsed))
		return nullptr;

	void * alignedStartAddress = AddOffset(mCurrentPos, memAlign);
	
	mCurrentPos = AddOffset(mCurrentPos, memUsed);

	LogAllocation(memUsed);
	
	return (void *)alignedStartAddress;
}

void LinearAllocator::Deallocate(void * p)
{
	ASSERT(0, "Please use Free for LinearAllocators");
}

void LinearAllocator::Free(void)
{
	mUsedMemory  = 0;
	mAllocations = 0;
	mCurrentPos = mMemoryPool;
#if ALLOCATOR_DEBUG
	memset(mMemoryPool, 0, mSize);
#endif
}
