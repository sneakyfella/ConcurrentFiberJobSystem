#pragma once

#define API_EXPORT			__declspec( dllexport )
#define API_IMPORT			__declspec( dllimport )


#if defined(_DEBUG)
	#define ALLOCATOR_DEBUG 1
	#define DEBUG_MODE 1
	#define CONSOLE_PRINT_MODE 0
#endif


#if defined(_MSC_VER)
	#define STDCALL __stdcall
#else
	#define STDCALL
#endif
