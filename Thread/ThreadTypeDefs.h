#pragma once
#include "ForwardDeclarations.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef HANDLE				   ThreadHandle, MutexHandle;
typedef void *                 FiberHandle;
typedef DWORD                  ThreadID, ThreadStatus, FiberID;
typedef CONDITION_VARIABLE     ConditionVariable, CV;
typedef CRITICAL_SECTION       CriticalSection, CS;

typedef void (STDCALL *FiberStartRoutine)(void *arg);
typedef LPTHREAD_START_ROUTINE ThreadStartRoutine;

typedef void(*JobFunction)(void* args);

#define FIBER_START_FUNCTION(func) void STDCALL func(void *arg)
#define FIBER_START_FUNCTION_CLASS_IMPL(className, func) void className::func(void *arg)

#define FIBER_RET_SIGNATURE void
#define THREAD_RET_SIGNATURE DWORD WINAPI

#define THREAD_LOCAL __declspec( thread )
#define TLS_VARIABLE(type, name) THREAD_LOCAL type name;
