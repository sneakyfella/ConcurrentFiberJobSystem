#pragma once

#include "ForwardDeclarations.h"
#include "FunctionLogger.h"
typedef std::chrono::steady_clock::time_point Timestamp;

class BaseProfiler : Noncopyable
{
public:
	BaseProfiler();
	virtual ~BaseProfiler();

	static void ProfileBegin(Timestamp & begin);

	static void ProfileEnd(Timestamp & end);

	virtual void DumpToFile(const Char * file) = 0;
};

#define PROFILER_BEGIN()\
Timestamp begin##__FUNCTION__;\
Timestamp end##__FUNCTION__;\
BaseProfiler::ProfileBegin(begin##__FUNCTION__);

#define PROFILER_END()\
BaseProfiler::ProfileEnd(end##__FUNCTION__);\
FunctionLogger::Instance().LogFunctionDuration(__FUNCTION__, std::chrono::duration<double, std::milli>(end##__FUNCTION__ - begin##__FUNCTION__).count());

#define PROFILER_BEGIN_W_NAME(name)\
Timestamp begin##__FUNCTION__;\
Timestamp end##__FUNCTION__;\
BaseProfiler::ProfileBegin(begin##__FUNCTION__);

#define PROFILER_END_W_NAME(name)\
BaseProfiler::ProfileEnd(end##__FUNCTION__);\
FunctionLogger::Instance().LogFunctionDuration(name, std::chrono::duration<double, std::milli>(end##__FUNCTION__ - begin##__FUNCTION__).count());
//Stdout << std::chrono::duration<double, std::milli>(end##__FUNCTION__ - begin##__FUNCTION__).count() << "ms" << Stdendl;