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

void FunctionLogger::WriteToFile(const Char * msg, const Char * file)
{
	for (auto & it : FunctionLog)
	{
		for (auto & iter : it.second)
		{
			Stdout << it.first << " : " << iter << "ms" << Stdendl;
		}
	}
}
