#pragma once
#include "ForwardDeclarations.h"
#include "ThreadTypeDefs.h"
#include "JobScheduler.h"
struct ThreadLocalStorage
{
	//Argument package
	JobScheduler * Scheduler;
	Thread *       OwningThread;

	FiberHandle    CurrentFiber;
	FiberHandle    NextFiber;

	FiberHandle    SwitchFiber;
	FiberHandle    CountWaitFiber;

	AtomicCounter * JobCounter;
	Uint32          JobValue;
};