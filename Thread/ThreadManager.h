#pragma once

#include "ForwardDeclarations.h"
#include "JThread.h"


class ThreadManager
{

public:

	ThreadManager(void);

	~ThreadManager(void);

	void Initialise(void);

	void Shutdown(void);

	void RunThreads(void);

private:
	Uint32 mPhysicalCoreCount;

	void CreateThreadPool(void);

	void FreeThreadPool(void);

	std::unordered_map<ThreadID, Thread*>  mThreadPool;


};

