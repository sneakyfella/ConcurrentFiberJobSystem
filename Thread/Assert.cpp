#include "stdafx.h"
#include <windows.h>
#include "Assert.h"

void Assert(char * const expression, const char * const  msg, const char * const filename, const size_t line, const char * func)
{
	String file(filename);

	size_t found = file.find_last_of('\\') + 1;
	Ostringstream msgBox;

	msgBox << expression << Stdendl
		<< "Msg  : " << msg << Stdendl
		<< "File : " << file.substr(found) << Stdendl
		<< "Func : " << func << Stdendl
		<< "Line : " << line;
	
	int res = ::MessageBox(nullptr, msgBox.str().c_str(), TEXT("ASSERT"), MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_DEFBUTTON2);

	switch (res)
	{
	case IDABORT:
		::exit(EXIT_FAILURE);
		break;

	case IDRETRY:
		::DebugBreak();
		break;

	case IDIGNORE:
		break;
	}
}

