#pragma once
#include "ForwardDeclarations.h"

void Assert(char * const expression, const char * msg, const char * filename, const size_t line, const char * func);


#define ASSERT(exp, msg)\
if((!exp))\
{\
	Ostringstream m(#msg);\
	Assert(#exp, m.str().c_str(), __FILE__, __LINE__, __FUNCTION__);\
}
#define ASSERT_TRUE(exp)\
if((!exp))\
{\
	Assert(#exp, "Expression is false. Expected true.",__FILE__, __LINE__, __FUNCTION__);\
}
#define ASSERT_FALSE(exp)\
if((exp))\
{\
	Assert(#exp, "Expression is true. Expected false.",__FILE__, __LINE__, __FUNCTION__);\
}