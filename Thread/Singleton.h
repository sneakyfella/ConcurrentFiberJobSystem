#pragma once

#define DECLARE_SINGLETON(type)\
public:\
static type & Instance(void)\
{\
	static type sTypeInstance;\
	return sTypeInstance;\
}\
static type* InstancePtr(void)\
{\
	return &Instance();\
}\
private:\
type(const type &);\
type&operator=(const type &);

#define GET_SINGLETON(type)\
type::Instance()