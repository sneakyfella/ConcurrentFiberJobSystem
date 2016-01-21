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

	//struct FunctionLog
	//{
	//	String Name;
	//	std::chrono::steady_clock::time_point  Time;
	//};

	void LogFunctionDuration(const String name, Float64 duration);

protected:
	virtual void WriteToFile(const Char * msg, const Char * file);
private:

	
	concurrency::concurrent_unordered_map<String, concurrency::concurrent_vector<Float64>> FunctionLog;

	//std::unordered_map < String, concurrency::concurrent_vector<Float64> >  FunctionLog;

	DECLARE_SINGLETON(FunctionLogger);
};