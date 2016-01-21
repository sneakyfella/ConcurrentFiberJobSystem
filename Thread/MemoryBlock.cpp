#include "stdafx.h"
#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(size_t MemoryBlockSize)
	: mPageSize(MemoryBlockSize)
	, mMemoryBlock(::operator new(MemoryBlockSize))
{
	
}

MemoryBlock::~MemoryBlock()
{
	::operator delete(mMemoryBlock);
}

void * MemoryBlock::GetMemoryBlock() const
{
	return mMemoryBlock;
}

void MemoryBlock::FlushMemoryBlock()
{
	memset(mMemoryBlock, 0, mPageSize);
}
