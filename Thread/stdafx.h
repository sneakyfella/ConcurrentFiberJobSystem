// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include "Config.h"
#include "ConvenienceMacros.h"
#include "Singleton.h"
#include "TypeDefs.h"
#include "Noncopyable.h"
#include "ServiceRegistry.h"
#include "ThreadTypeDefs.h"


//Math
#include "MathFunctions.h"
#include "MathCompares.h"
#include "Vector2.h"
#include "Vector3.h"
// Memory
#include "MemoryBlock.h"
#include "Allocator.h"
#include "LinearAllocator.h"
#include "FreeListAllocator.h"
#include "StackAllocator.h"
#include "TaggedHeap.h"

// Objects
#include "Object.h"
#include "ObjectComponent.h"
#include "ObjectManager.h"

// Frames
#include "FrameParam.h"
#include "FrameManager.h"

// Execution Stages
#include "ExecutionStage.h"
#include "Executor.h"
//Debug
#include "Assert.h"
#include "BaseLogger.h"
#include "FunctionLogger.h"
#include "BaseProfiler.h"
// User Defined containers
#include "ConcurrentQueue.h"


// Threading
#include "ThreadLocalStorage.h"
#include "JThread.h"
#include "ThreadManager.h"
#include "Fiber.h"
#include "FiberManager.h"
#include "Job.h"
#include "JobScheduler.h"




// TODO: reference additional headers your program requires here
