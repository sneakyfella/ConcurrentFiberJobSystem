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