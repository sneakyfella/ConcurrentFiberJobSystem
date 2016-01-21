#include "stdafx.h"

BaseLogger::BaseLogger(void)
{
}

BaseLogger::~BaseLogger(void)
{
}

void BaseLogger::Write(const Char * msg, const Char * file)
{
	WriteToFile(msg, file);
}
