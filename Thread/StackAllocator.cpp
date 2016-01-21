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
