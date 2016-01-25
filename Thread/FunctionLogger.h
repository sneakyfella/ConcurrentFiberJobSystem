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

protected:
	virtual void WriteToFile(const Char * msg, const Char * file);
private:

    typedef String                                  FunctionName;
    typedef concurrency::concurrent_vector<Float64> FunctionTimeStamps;
	
	concurrency::concurrent_unordered_map<FunctionName, FunctionTimeStamps> FunctionLog;

	DECLARE_SINGLETON(FunctionLogger);
};