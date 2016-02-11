// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include "../Thread/Config.h"
#include "../Thread/ConvenienceMacros.h"
#include "../Thread/Singleton.h"
#include "../Thread/TypeDefs.h"
#include "../Thread/Noncopyable.h"
#include "../Thread/ServiceRegistry.h"
#include "../Thread/ThreadTypeDefs.h"


//Math
#include "../Thread/MathFunctions.h"
#include "../Thread/MathCompares.h"
// Memory
#include "../Thread/MemoryBlock.h"
#include "../Thread/Allocator.h"
#include "../Thread/LinearAllocator.h"
#include "../Thread/FreeListAllocator.h"
#include "../Thread/StackAllocator.h"
#include "../Thread/TaggedHeap.h"

// Objects
#include "../Thread/Object.h"
#include "../Thread/ObjectComponent.h"
#include "../Thread/ObjectManager.h"

// Frames
#include "../Thread/FrameParam.h"
#include "../Thread/FrameManager.h"

// Execution Stages
#include "../Thread/ExecutionStage.h"
#include "../Thread/Executor.h"
//Debug
#include "../Thread/Assert.h"
#include "../Thread/BaseLogger.h"
#include "../Thread/FunctionLogger.h"
#include "../Thread/BaseProfiler.h"
// User Defined containers
#include "../Thread/ConcurrentQueue.h"


// Threading
#include "../Thread/ThreadLocalStorage.h"
#include "../Thread/JThread.h"
#include "../Thread/ThreadManager.h"
#include "../Thread/Fiber.h"
#include "../Thread/FiberManager.h"
#include "../Thread/Job.h"
#include "../Thread/JobScheduler.h"

// Tests
// TODO: reference additional headers your program requires here
