#pragma once
#include "ForwardDeclarations.h"
#include "ThreadTypeDefs.h"

class Fiber
{
public:
	Fiber();
	~Fiber();

	virtual void Initialise(void);

	virtual void Shutdown(void);

	FiberID GetFiberID(void) const;

	FiberHandle CBLFiberHandle(void);

	void SetFiberID(FiberID id);

	static void CBLSwitchToFiber(FiberHandle fiberToSwitchTo);

private:

	FiberHandle CBLCreateFiber(FiberStartRoutine startRout, size_t stackSize, void * args, FiberID id);

	void CBLDeleteFiber(void);

	void CBLConvertFiberToThread(void);

	void CBLConvertThreadToFiber(void);

	

	//FiberHandle CBLFiberHandle(void);

	FiberID         mFiberID;
	FiberHandle     mFiberHandle;

	friend class Thread;
	friend class FiberManager;
};
