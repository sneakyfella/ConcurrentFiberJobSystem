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
#include "ThreadTypeDefs.h"

class Fiber
{
    /***** Public Methods *****/
public:
    //! Default constructor.
	Fiber();
    //! Default destructor.
	~Fiber();
    //! Fiber initialisation method.
	void Initialise(void);
    //! Fiber shutdown method.
	void Shutdown(void);
    //! static function for fibers to switch to
    //! @param	fiberToSwitchTo	 Fiber to switch to
	static void CBLSwitchToFiber(FiberHandle fiberToSwitchTo);

    /***** Property Methods *****/
public:
    GETSET_AUTO(FiberID, FiberID);

    FiberHandle CBLFiberHandle(void);
    /***** Private Methods *****/
private:
    //! Only Manager should be creating fibers
    //! static function for fibers to switch to
    //! @param	startRout	 Fiber start routine
    //! @param	stackSize	 Fiber's stack space, 0 for default 
    //! @param	args	 POinter to scheduler in this case, not really needed as we are using TLS
    //! @param	id	 Arbitrary ID for debugging
    //! @return	FiberHandle	 fiber handle 
	FiberHandle CBLCreateFiber(FiberStartRoutine startRout, size_t stackSize, void * args, FiberID id);

    //! Free handle
	void CBLDeleteFiber(void);
    //! Converts a fiber back to a thread
	void CBLConvertFiberToThread(void);
    //! Converts a thread to a fiber
	void CBLConvertThreadToFiber(void);


	FiberID         mFiberID;
	FiberHandle     mFiberHandle;

	friend class Thread;
	friend class FiberManager;
};
