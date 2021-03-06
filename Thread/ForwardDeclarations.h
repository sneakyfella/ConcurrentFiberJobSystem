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
#pragma once

#include "TypeDefs.h"
#include "Config.h"
#include "ConvenienceMacros.h"

class Noncopyable;

class Object;
class ObjectComponent;
class ObjectManager;

class Thread;
class ThreadManager;
class Fiber;
class FiberManager;

class Job;
class JobScheduler;

class Allocator;
class FreeListAllocator;
class LinearAllocator;
class StackAllocator;

class MemoryBlock;
class TaggedHeap;

class BaseLogger;
class FunctionLogger;
class FileLogger;
class BaseProfiler;
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <algorithm>
#include <functional>
#include <limits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <initializer_list>
#include <chrono>
#include <ctime>
#include <thread>