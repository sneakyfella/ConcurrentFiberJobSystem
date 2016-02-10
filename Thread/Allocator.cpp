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
#include "Allocator.h"

BaseAllocator::BaseAllocator(Uint32 size)
    : mMemoryPool(::operator new(size))
    , mTaggedHeapBlock(nullptr)
    , mSize(size)
    , mUsedMemory(0)
    , mAllocations(0)
    , mUsingTaggedHeap(false)
{
}

BaseAllocator::BaseAllocator(Uint32 size, MemoryBlock * memPool)
    : mMemoryPool(nullptr)
    , mTaggedHeapBlock(memPool)
    , mSize(size)
    , mUsedMemory(0)
    , mAllocations(0)
    , mUsingTaggedHeap(true)
{
    // Point to mem block's mem pool
    mMemoryPool = mTaggedHeapBlock->GetMemoryBlock();
}

BaseAllocator::~BaseAllocator(void)
{
    if(!mUsingTaggedHeap)
	    ::operator delete(mMemoryPool);
    else
    {
        mTaggedHeapBlock->FlushMemoryBlock();
    }

	ASSERT(mUsedMemory != 0 || mAllocations != 0, "Memory Leak");
}

void BaseAllocator::LogAllocation(Uint32 size)
{
	++mAllocations;
	mUsedMemory += size;
}

void BaseAllocator::LogDeallocation(Uint32 size)
{
	--mAllocations;
	mUsedMemory -= size;
}

