#pragma once
#include "ForwardDeclarations.h"

class StackAllocator : public BaseAllocator
{
public:
	StackAllocator(size_t poolSize);

	virtual ~StackAllocator(void);

	virtual void * Allocate(Uint32 size, Uint8 alignment = 8) override;

	virtual void Deallocate(void * p) override;

	virtual void Free(void) override;

	struct StackBlockAllocationHeader
	{
		StackBlockAllocationHeader()
		{}

#if ALLOCATOR_DEBUG
		explicit StackBlockAllocationHeader(Uint32 size, void * memStart)
			: mBlockStart(memStart)
			, mBlockSize(size)
		{}
		void * mBlockStart = nullptr;
#else
		explicit StackBlockAllocationHeader(Uint32 size, void * memStart = nullptr)
			, mBlockSize(size)
		{}
#endif
		Uint32 mBlockSize = 0;
	};


private:
	void * mPrevPos;
	void * mCurrentPos;
};