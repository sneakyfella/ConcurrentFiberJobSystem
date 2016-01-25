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
#include "FunctionLogger.h"
#include "BaseLogger.h"
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