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
#include "BaseLogger.h"
#include <concurrent_unordered_map.h>
#include <concurrent_vector.h>
class FunctionLogger : public BaseLogger
{
public:
	FunctionLogger(void);
	virtual ~FunctionLogger(void);


	void LogFunctionDuration(const String name, Float64 duration);

    Uint32 GetFunctionLogSize(const String name);

    void ClearFunctionLog(void);

protected:
	virtual void WriteToFile(const Char * msg, const Char * file);


private:

    typedef String                                  FunctionName;
    typedef concurrency::concurrent_vector<Float64> FunctionTimeStamps;
	
	concurrency::concurrent_unordered_map<FunctionName, FunctionTimeStamps> FunctionLog;

	DECLARE_SINGLETON(FunctionLogger);
};