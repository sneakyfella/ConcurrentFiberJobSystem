#include "stdafx.h"
#include "TaggedHeap.h"
#include <utility>

TaggedHeap::TaggedHeap(size_t pageSize)
: MemoryBlockSize(pageSize)
{
    // Initial Allocation
    AllocateMemoryBlocks();
}

TaggedHeap::~TaggedHeap()
{
}

MemoryBlock * TaggedHeap::GetMemoryBlock(const Char * tag)
{
	size_t hash = std::hash<const Char *>()(tag);

	mLock.lock();
	if (mFreeMemory.empty())
	{
		AllocateMemoryBlocks();
	}
	MemoryBlock * ret = mFreeMemory.back();

    // Setting
    ret->SetTag(tag);
	mUsedMemory[hash].push_back(ret);
	mFreeMemory.pop_back();
	mLock.unlock();
	return ret;
}



void TaggedHeap::FreeMemoryBlocksWithTag(const Char * tag)
{
	
    size_t hash = std::hash<const Char *>()(tag);
	mLock.lock();
#ifdef ALLOCATOR_DEBUG
    FlushMemory(hash);
#endif

	mFreeMemory.insert(mFreeMemory.end(), mUsedMemory[hash].begin(), mUsedMemory[hash].end());
	mUsedMemory[hash].clear();
	mLock.unlock();
}

void TaggedHeap::FlushMemory(size_t hash)
{
    CBL_FORRANGEREF(mUsedMemory[hash], it)
    {
        it->FlushMemoryBlock();
    }
}

void TaggedHeap::AllocateMemoryBlocks(Uint32 num)
{
	// No need for lock as GetMemoryBlock(const Char * tag) will lock
	for (Uint32 i = 0; i < num; ++i)
	{
		MemoryBlock * ptr = new MemoryBlock(MemoryBlockSize);
		mFreeMemory.push_back(ptr);
	}
}
