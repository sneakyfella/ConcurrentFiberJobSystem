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
    if(mUsingTaggedHeap)
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

