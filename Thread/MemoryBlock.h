#pragma once
#include "ForwardDeclarations.h"

static const size_t sDefaultPageSize = KILOBYTES(2);

class MemoryBlock
{
public:
	MemoryBlock(size_t MemoryBlockSize = sDefaultPageSize);
	~MemoryBlock();

	void * GetMemoryBlock() const;
	
	void FlushMemoryBlock();

private:
	const size_t mPageSize;
	void * mMemoryBlock;
};

