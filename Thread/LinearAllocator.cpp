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
