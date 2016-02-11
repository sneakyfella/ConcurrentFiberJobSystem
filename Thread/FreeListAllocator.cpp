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
#include "FreeListAllocator.h"

FreeListAllocator::FreeListAllocator(size_t poolSize, Uint8 alignment)
	:BaseAllocator(poolSize)
{
    mHead = reinterpret_cast<FreeBlock*>( mMemoryPool );
}

FreeListAllocator::FreeListAllocator(size_t poolSize, Uint8 alignment, MemoryBlock * memPool)
    :BaseAllocator(poolSize, memPool)
{
}

FreeListAllocator::~FreeListAllocator(void)
{

}

void * FreeListAllocator::Allocate(Uint32 size, Uint8 alignment)
{
    // TODO : MEM ALIGN IT JUST LIKE LINEAR AND STACK ALLOCATOR

	ASSERT(size == 0, "Size = 0");
    
    FreeBlock* prev = nullptr;
    FreeBlock* curr = mHead;

    Uint32 sizeWithHeader = size + sizeof(FreeBlock);

    while (curr)
    {
        // If current free list block is too small for allocated size
        if (curr->Size < sizeWithHeader)
        {
            prev = curr;
            curr = curr->Next;
            continue;
        }
        //Else we can just slice a chunk out of it to give to user
        // Init-ing new sliced block, connecting new slice to nodes in front
        FreeBlock * next = (FreeBlock *)AddOffset(curr, sizeWithHeader);

        // if carved block is not entirely consumed, we modify it's size
        if (curr->Size - sizeWithHeader > 0)
        {
            next->Size = curr->Size - sizeWithHeader;
            next->Next = curr->Next;
        }

        // connecting the prev block to the newly sliced block
        if (prev)
        {
            // If the entire "next block" has been consumed by incoming request
            // next ptr points directly to the next block
            prev->Next = (curr->Size - sizeWithHeader > 0) ? next : curr->Next;
        }
        // it is a new head
        else
            mHead = next;

        // Log the allocation
        LogAllocation(sizeWithHeader);

        // Setting new block size before returning user pointer
        curr->Size = sizeWithHeader;
        curr->Next = nullptr;

        void * ret = AddOffset(curr, sizeof(FreeBlock));
        return ret;
    }

	return nullptr;
}

void FreeListAllocator::Free(void)
{
    mUsedMemory = 0;
    mAllocations = 0;


    // Just flushing memory
#if ALLOCATOR_DEBUG
    memset(mHead, 0, mSize);
#endif
}

void FreeListAllocator::Deallocate(void * p)
{
    ASSERT(p == 0, "Tried to free nullptr");

    // Get the header details
    FreeBlock * header = (FreeBlock *)SubtractOffset(p, sizeof(FreeBlock));

    // Get data size
    int dataSize = header->Size - sizeof(FreeBlock);
    //memset( p, 0, dataSize); // NOTE, could improve deallocation performance by not memsetting.

    //Connecting new block
    header->Next = mHead;
    // Make this the new head
    mHead = header;
    // Log the deallocation
    LogDeallocation(header->Size);
}
