/* This source file is part of the concurrent Fiber based Framework.
*
* Copyright (c) 2015-2016 Joshua Chew
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
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

    void ReturnMemoryBlock(MemoryBlock* ptr);

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