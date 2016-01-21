#include "stdafx.h"
#include "BaseProfiler.h"

BaseProfiler::BaseProfiler()
{
}

BaseProfiler::~BaseProfiler()
{
}

void BaseProfiler::ProfileBegin(Timestamp & begin)
{
	begin = std::chrono::high_resolution_clock::now();
}

void BaseProfiler::ProfileEnd(Timestamp & end)
{
	
	end = std::chrono::high_resolution_clock::now();
}
