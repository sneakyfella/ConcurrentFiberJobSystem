#pragma once
#include "ForwardDeclarations.h"

class GlobalStorage
{
public:
	GlobalStorage(void);
	~GlobalStorage(void);




	DECLARE_SINGLETON(GlobalStorage);
};