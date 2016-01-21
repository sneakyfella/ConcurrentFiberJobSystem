#pragma once

#include "ForwardDeclarations.h"

class BaseLogger : Noncopyable
{
public:
	BaseLogger(void);
	virtual ~BaseLogger(void);

	void Write(const Char * msg, const Char * file);

protected:
	virtual void WriteToFile(const Char * msg, const Char * file) = 0;

};