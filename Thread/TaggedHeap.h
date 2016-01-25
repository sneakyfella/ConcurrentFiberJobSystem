#pragma once
#include "ForwardDeclarations.h"

#include "MemoryBlock.h"
#include <mutex>
class TaggedHeap
{
public:

	TaggedHeap(size_t pageSize = KILOBYTES(2));
	~TaggedHeap();

	MemoryBlock * GetMemoryBlock(const Char *);

	void FreeMemoryBlocksWithTag(const Char *);

private:
    void FlushMemory(size_t hash);

	void AllocateMemoryBlocks(Uint32 num = 5);

	const Uint32 MemoryBlockSize;

	std::unordered_map<Uint32, std::vector<MemoryBlock *>> mUsedMemory;
	std::vector<MemoryBlock *> mFreeMemory;

	std::mutex mLock;

    DECLARE_SINGLETON(TaggedHeap);
};