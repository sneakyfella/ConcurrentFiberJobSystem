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
#if ALLOCATOR_DEBUG
	void * mPrevPos;
#endif
	void * mCurrentPos;
};