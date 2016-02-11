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
#include "stdafx.h"
#include "FunctionLogger.h"

FunctionLogger::FunctionLogger(void)
{
}

FunctionLogger::~FunctionLogger(void)
{
}

void FunctionLogger::LogFunctionDuration(const String name, Float64 duration)
{
	FunctionLog[name].push_back(duration);
}

Uint32 FunctionLogger::GetFunctionLogSize(const String name)
{
    return FunctionLog[name].size();
}

void FunctionLogger::ClearFunctionLog(void)
{
    for (auto & it : FunctionLog)
    {
        it.second.clear();
    }

    FunctionLog.clear();
}

void FunctionLogger::WriteToFile(const Char * msg, const Char * file)
{
    // TODO : WRITE TO A DAMN FILE SON
	for (auto & it : FunctionLog)
	{
		for (auto & iter : it.second)
		{
			Stdout << it.first << " : " << iter << "ms" << Stdendl;
		}
	}
}
