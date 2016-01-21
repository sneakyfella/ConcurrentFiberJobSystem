#pragma once
#include "ForwardDeclarations.h"

class LinearAllocator : public BaseAllocator
{
public:
	LinearAllocator(size_t poolSize);

    LinearAllocator(Uint32 size, MemoryBlock * memPool);

	virtual ~LinearAllocator(void);

	virtual void * Allocate(Uint32 size, Uint8 alignment = 8) override;

	virtual void Deallocate(void * p) override;

	virtual void Free(void) override;
private:
	void * mCurrentPos;
};