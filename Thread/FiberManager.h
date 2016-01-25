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
#include "Fiber.h"
#include <concurrent_queue.h>
class FiberManager
{
public:
	FiberManager(Uint32 fiberCount = 100);
	~FiberManager();

	void Initialise(void);

	void Shutdown(void);

	FiberHandle PopFreeFiber(void);

	void PushFreeFiber(FiberHandle hnd);

	typedef std::unordered_map<Uint32, Fiber *>                FiberPool;
	typedef concurrency::concurrent_queue<FiberHandle>         FiberQueue;
private:

	void CreateFiberPool(void);

	void FreeFiberPool(void);

	Uint32 mFiberCount;

	FiberPool  mFiberPool;
	FiberQueue mFiberQueue;
};