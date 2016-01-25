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
#include "stdafx.h"
#include "Fiber.h"

Fiber::Fiber()
: mFiberHandle(nullptr)
{
}

Fiber::~Fiber()
{
}

void Fiber::Initialise(void)
{
}

void Fiber::Shutdown(void)
{
	CBLDeleteFiber();
}

FiberID Fiber::GetFiberID(void) const
{
	return mFiberID;
}

void Fiber::SetFiberID(FiberID id)
{
	mFiberID = id;
}



FiberHandle Fiber::CBLCreateFiber(FiberStartRoutine startRout, size_t stackSize, void * args, FiberID id)
{
	// CreateFiberEx creates a fiber in a suspended state.
	// As opposed to CreateFiber
	mFiberHandle = CreateFiberEx(stackSize, 0, FIBER_FLAG_FLOAT_SWITCH, startRout, args);
	mFiberID = id;
	if (!mFiberHandle)
	{
		Stdout << "Error creating fiber" << Stdendl;
	}

	return mFiberHandle;

}

void Fiber::CBLDeleteFiber(void)
{
	DeleteFiber(mFiberHandle);
}

void Fiber::CBLConvertFiberToThread(void)
{
	ConvertFiberToThread();
}

void Fiber::CBLConvertThreadToFiber(void)
{
	// Continue to be suspended after switch
	ConvertThreadToFiberEx(nullptr, FIBER_FLAG_FLOAT_SWITCH);
}

void Fiber::CBLSwitchToFiber(FiberHandle fiberToSwitchTo)
{
	SwitchToFiber(fiberToSwitchTo);
}

FiberHandle Fiber::CBLFiberHandle(void)
{
	return mFiberHandle ? (mFiberHandle) : nullptr;
}
