#pragma once
#include "ForwardDeclarations.h"
#include "AllocatorAlignmentFunctions.h"

class BaseAllocator : Noncopyable
{
public:
	BaseAllocator(Uint32 size);

    BaseAllocator(Uint32 size, MemoryBlock * memPool);

	virtual ~BaseAllocator(void);

	virtual void * Allocate(Uint32 size, Uint8 alignment = 8) = 0;

	virtual void Deallocate(void * p) = 0;

	virtual void Free(void) = 0;


	inline bool CheckAllocatorOverflow(size_t incomingMem) const {
		return (mUsedMemory + incomingMem) > mSize;
	}
	inline void * GetStart(void) const {
		return mMemoryPool;
	}
	inline void * GetEnd(void) const {
		return AddOffset(mMemoryPool, mSize);
	}
	inline Uint32 GetSize(void) const {
		return mSize;
	}
	inline Uint32 GetUsedMemory(void) const {
		return mUsedMemory;
	}
	inline Uint32 GetNumberOfAllocations(void) const {
		return mAllocations;
	}

protected:

	void LogAllocation(Uint32 size);
	void LogDeallocation(Uint32 size);

	void * mMemoryPool;
    MemoryBlock * mTaggedHeapBlock;
    bool mUsingTaggedHeap;
	Uint32   mSize;
	Uint32   mUsedMemory;
	Uint32   mAllocations;
};

