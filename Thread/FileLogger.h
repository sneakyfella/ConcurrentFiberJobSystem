#pragma once
#include "ForwardDeclarations.h"
#include "BaseLogger.h"

class FileLogger : public BaseLogger
{
public:
	FileLogger(void);
	virtual ~FileLogger(void);

	void Write(const Char * msg, const Char * file);

protected:
	virtual void WriteToFile(const Char * msg, const Char * file);
private:

};