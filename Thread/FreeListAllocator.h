#pragma once
#include "ForwardDeclarations.h"

class FreeListAllocator : public BaseAllocator
{
public:
	FreeListAllocator(size_t size, size_t blockSize, Uint8 alignment);

    FreeListAllocator(size_t size, size_t blockSize, Uint8 alignment, MemoryBlock * memPool);

	virtual ~FreeListAllocator(void);

	virtual void * Allocate(Uint32 size, Uint8 alignment = 8) override;

	virtual void Deallocate(void * p) override;

	virtual void Free(void) override;

	
private:
	typedef std::unordered_map<Uint32, void *> MemoryPool;


	Uint32 mBlockSize;
	MemoryPool  mUnusedPool;
	MemoryPool  mUsedPool;
};