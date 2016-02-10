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

