#include "stdafx.h"
#include "FreeListAllocator.h"

FreeListAllocator::FreeListAllocator(size_t poolSize, size_t blockSize, Uint8 alignment)
	:BaseAllocator(poolSize)
	, mBlockSize(blockSize)
{

}

FreeListAllocator::FreeListAllocator(size_t poolSize, size_t blockSize, Uint8 alignment, MemoryBlock * memPool)
    :BaseAllocator(poolSize, memPool)
    , mBlockSize(blockSize)
{
}

FreeListAllocator::~FreeListAllocator(void)
{

}

void * FreeListAllocator::Allocate(Uint32 size, Uint8 alignment)
{
	ASSERT(size == 0, "Size = 0");

	return nullptr;
}

void FreeListAllocator::Free(void)
{
}

void FreeListAllocator::Deallocate(void * p)
{
}
