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
    //! Default constructor.
	FiberManager(Uint32 fiberCount = 100);
    //! Default destructor.
	~FiberManager();
    //! FiberManager initialisation method.
    //! Creates the fiber pool in suspended state
	void Initialise(void);
    //! FiberManager Shutdown method.
    //! Shutsdown the fiber pool 
	void Shutdown(void);

    //! Getting a free fiber for user method.
    //! @return	Handle to a free fiber from fiber pool
	FiberHandle PopFreeFiber(void);
    //! Returning a free fiber for user method.
    //! @param	hnd Handle to fiber from fiber pool
	void PushFreeFiber(FiberHandle hnd);


private:

	void CreateFiberPool(void);

	void FreeFiberPool(void);

	Uint32 mFiberCount;

    typedef std::unordered_map<Uint32, Fiber *>                FiberPool;
    typedef concurrency::concurrent_queue<FiberHandle>         FiberQueue;

	FiberPool  mFiberPool; // Just for tracking purposes
	FiberQueue mFiberQueue; // Actual queue to give to users
};