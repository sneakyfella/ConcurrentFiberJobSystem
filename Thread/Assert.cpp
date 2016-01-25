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

