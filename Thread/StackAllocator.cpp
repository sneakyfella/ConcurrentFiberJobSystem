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

#include "StackAllocator.h"

StackAllocator::StackAllocator(size_t poolSize)
	:BaseAllocator(poolSize)
	, mPrevPos(nullptr)
	, mCurrentPos(BaseAllocator::GetStart())
{

}

StackAllocator::~StackAllocator(void)
{

}

void * StackAllocator::Allocate(Uint32 size, Uint8 alignment)
{
	ASSERT(size == 0, "Size = 0");

	Uint8 memAlign = AlignForwardWithHeader(mCurrentPos, alignment, sizeof(StackBlockAllocationHeader));

	Uint32 memUsed = size + sizeof(StackBlockAllocationHeader);

	if (CheckAllocatorOverflow(memUsed + memAlign))
		return nullptr;

#if ALLOCATOR_DEBUG
	mPrevPos = mCurrentPos;
#endif

	void * alignedStartAddress = AddOffset(mCurrentPos, memAlign);

	// block header for allocated stack block, before moving the current pos ptr;
	StackBlockAllocationHeader * blockHeaderPtr = reinterpret_cast<StackBlockAllocationHeader *>(alignedStartAddress);
	blockHeaderPtr->mBlockSize = memUsed;
	blockHeaderPtr->mBlockStart = alignedStartAddress;

	mCurrentPos = AddOffset(mCurrentPos, memUsed);

	LogAllocation(memUsed);

	return (void*)alignedStartAddress;
}

void StackAllocator::Free(void)
{
	mUsedMemory = 0;
	mAllocations = 0;
	mCurrentPos = mMemoryPool;
#if ALLOCATOR_DEBUG
	memset(mMemoryPool, 0, mSize);
#endif
}

void StackAllocator::Deallocate(void * p)
{
#if ALLOCATOR_DEBUG
	ASSERT((p != mPrevPos), "Incorrect Deallocation, pointer is not last mem addr");
#endif

	StackBlockAllocationHeader * blockHeadPtr = reinterpret_cast<StackBlockAllocationHeader *>(p);
	
	mCurrentPos = SubtractOffset(mCurrentPos, blockHeadPtr->mBlockSize);

	LogDeallocation(blockHeadPtr->mBlockSize);
}
